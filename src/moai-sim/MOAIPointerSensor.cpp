// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIPointerSensor.h>
#include <moai-sim/MOAIInputMgr.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	getLoc
	@text	Returns the location of the pointer on the screen.

	@in		MOAIPointerSensor self
	@out	number x
	@out	number y
*/
int MOAIPointerSensor::_getLoc ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPointerSensor, "U" )

	lua_pushnumber ( state, self->mX );
	lua_pushnumber ( state, self->mY );

	return 2;
}

//----------------------------------------------------------------//
/**	@lua	setCallback
	@text	Sets or clears the callback to be issued when the pointer location changes.

	@in		MOAIPointerSensor self
	@opt	function callback			Default value is nil.
	@out	nil
*/
int MOAIPointerSensor::_setCallback ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPointerSensor, "U" )
	
	self->mOnMove.SetRef ( state, 2 );
	
	return 0;
}

//================================================================//
// MOAIPointerSensor
//================================================================//

//----------------------------------------------------------------//
void MOAIPointerSensor::EnqueuePointerEvent ( ZLIndex deviceID, ZLIndex sensorID, int x, int y ) {

	MOAIInputMgr& inputMgr = MOAIInputMgr::Get ();
	if ( inputMgr.WriteEventHeader < MOAIPointerSensor >( deviceID, sensorID )) {
		inputMgr.Write < int >( x );
		inputMgr.Write < int >( y );
	}
}

//----------------------------------------------------------------//
MOAIPointerSensor::MOAIPointerSensor () {

	RTTI_SINGLE ( MOAIPointerSensor, MOAISensor )
}

//----------------------------------------------------------------//
MOAIPointerSensor::~MOAIPointerSensor () {
}

//----------------------------------------------------------------//
void MOAIPointerSensor::ParseEvent ( ZLStream& eventStream ) {

	int x = eventStream.Read < int >( 0 );
	int y = eventStream.Read < int >( 0 );

	this->mX = x;
	this->mY = y;
	
	if ( this->mOnMove ) {
		MOAIScopedLuaState state = this->mOnMove.GetSelf ();
		lua_pushnumber ( state, this->mX );
		lua_pushnumber ( state, this->mY );
		state.DebugCall ( 2, 0 );
	}
}

//================================================================//
// virtual
//================================================================//

//----------------------------------------------------------------//
void MOAIPointerSensor::MOAILuaObject_RegisterLuaClass ( MOAIComposer& composer, MOAILuaState& state ) {

	MOAI_CALL_SUPER_ONCE ( composer, MOAISensor, MOAILuaObject_RegisterLuaClass ( composer, state ));
}

//----------------------------------------------------------------//
void MOAIPointerSensor::MOAILuaObject_RegisterLuaFuncs ( MOAIComposer& composer, MOAILuaState& state ) {

	MOAI_CALL_SUPER_ONCE ( composer, MOAISensor, MOAILuaObject_RegisterLuaFuncs ( composer, state ));

	luaL_Reg regTable [] = {
		{ "getLoc",			_getLoc },
		{ "setCallback",	_setCallback },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
