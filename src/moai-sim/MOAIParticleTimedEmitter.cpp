// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIParticleTimedEmitter.h>
#include <moai-sim/MOAIParticleSystem.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	setFrequency
	@text	Set timer frequency.
	
	@in		MOAIParticleTimedEmitter self
	@in		number min
	@opt	number max		Default value is min.
	@out	nil
*/
int MOAIParticleTimedEmitter::_setFrequency ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleTimedEmitter, "UN" )

	float min = state.GetValue < float >( 2, 1.0f );
	float max = state.GetValue < float >( 3, min );

	self->SetFrequencyRange ( min, max );
	return 0;
}

//================================================================//
// MOAIParticleTimedEmitter
//================================================================//

//----------------------------------------------------------------//
float MOAIParticleTimedEmitter::GetRandomFrequency () {

	return ZLFloat::Rand ( this->mMinFrequency, this->mMaxFrequency );
}

//----------------------------------------------------------------//
MOAIParticleTimedEmitter::MOAIParticleTimedEmitter () :
	mTime ( 0.0f ),
	mEmitTime ( 0.0f ),
	mMinFrequency ( 1.0f ),
	mMaxFrequency ( 1.0f ) {
	
	RTTI_BEGIN ( MOAIParticleTimedEmitter )
		RTTI_EXTEND ( MOAIParticleEmitter )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIParticleTimedEmitter::~MOAIParticleTimedEmitter () {
}

//----------------------------------------------------------------//
void MOAIParticleTimedEmitter::SetFrequencyRange ( float min, float max ) {

	this->mMinFrequency = min;
	this->mMaxFrequency = max;
}

//================================================================//
// virtual
//================================================================//

//----------------------------------------------------------------//
void MOAIParticleTimedEmitter::MOAIAction_Update ( double step ) {

	this->mTime += ( float )step;
	if ( !this->mSystem ) return;
	if ( this->mTime < this->mEmitTime ) return;
	
	u32 emission = this->GetRandomEmission ();
	this->Surge ( emission );
	
	this->mEmitTime = this->mTime + this->GetRandomFrequency ();
}

//----------------------------------------------------------------//
void MOAIParticleTimedEmitter::MOAILuaObject_RegisterLuaClass ( MOAIComposer& composer, MOAILuaState& state ) {

	MOAI_CALL_SUPER_ONCE ( composer, MOAIParticleEmitter, MOAILuaObject_RegisterLuaClass ( composer, state ));
}

//----------------------------------------------------------------//
void MOAIParticleTimedEmitter::MOAILuaObject_RegisterLuaFuncs ( MOAIComposer& composer, MOAILuaState& state ) {
	
	MOAI_CALL_SUPER_ONCE ( composer, MOAIParticleEmitter, MOAILuaObject_RegisterLuaFuncs ( composer, state ));
	
	luaL_Reg regTable [] = {
		{ "setFrequency",		_setFrequency },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}
