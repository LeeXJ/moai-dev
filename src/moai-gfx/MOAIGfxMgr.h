// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIGFXMGR_H
#define	MOAIGFXMGR_H

#include <moai-gfx/MOAIGfxMgr_CPUCache.h>
#include <moai-gfx/MOAIGfxMgr_GPUCache.h>
#include <moai-gfx/MOAIGfxMgr_RenderTree.h>
#include <moai-gfx/MOAIGfxMgr_VertexCache.h>
#include <moai-gfx/MOAIGfxMgrComponents.h>
#include <moai-gfx/MOAIGfxPresetEnum.h>

class MOAIImageTexture;
class MOAITexture2D;

//================================================================//
// MOAIGfxMgr
//================================================================//
/**	@lua	MOAIGfxMgr
	@text	Interface to the graphics singleton.
	
	@const	EVENT_RESIZE
*/
class MOAIGfxMgr :
	public ZLContextClassAlias < MOAIGfxMgr >,
	public virtual MOAIGlobalEventSource,
	public virtual MOAIGfxMgrComponents,
	public virtual MOAIGfxMgr_CPUCache,
	public virtual MOAIGfxMgr_GPUCache,
	public virtual MOAIGfxMgr_RenderTree,
	public virtual MOAIGfxMgr_VertexCache {
protected:

	//----------------------------------------------------------------//
	virtual MOAIShader*			MOAIGfxMgr_AffirmShader				( MOAILuaState& state, int idx ) const = 0;
	virtual MOAITexture*		MOAIGfxMgr_AffirmTexture			( MOAILuaState& state, int idx ) const = 0;
	virtual MOAIImageTexture*	MOAIGfxMgr_CreateImageTexture		() const = 0;
	virtual MOAIIndexBuffer*	MOAIGfxMgr_CreateIndexBuffer		() const = 0;
	virtual MOAITexture2D*		MOAIGfxMgr_CreateTexture2D			() const = 0;
	virtual MOAIVertexArray*	MOAIGfxMgr_CreateVertexArray		() const = 0;
	virtual MOAIVertexBuffer*	MOAIGfxMgr_CreateVertexBuffer		() const = 0;
	virtual MOAIVertexFormat*	MOAIGfxMgr_CreateVertexFormat		() const = 0;
	virtual MOAIShader*			MOAIGfxMgr_GetShaderPreset			( MOAIShaderPresetEnum preset ) const = 0;
	virtual size_t				MOAIGfxMgr_GetTextureMemoryUsage	() const = 0;
	virtual void				MOAIGfxMgr_PopState					() = 0;
	virtual void				MOAIGfxMgr_PushState				() = 0;
	

	//----------------------------------------------------------------//
	MOAIGfxMgr_CPUCache&		MOAIGfxMgrComponents_GetCPUCache		();
	MOAIGfxMgr&					MOAIGfxMgrComponents_GetGfxMgr			();
	MOAIGfxMgr_GPUCache&		MOAIGfxMgrComponents_GetGPUCache		();
	MOAIGfxMgr_RenderTree&		MOAIGfxMgrComponents_GetRenderTree		();
	MOAIGfxMgr_VertexCache&		MOAIGfxMgrComponents_GetVertexCache		();
	void						MOAILuaObject_RegisterLuaClass			( MOAIComposer& composer, MOAILuaState& state );
	void						MOAILuaObject_RegisterLuaFuncs			( MOAIComposer& composer, MOAILuaState& state );
	void						ZLContextClass_Finalize					();
	void						ZLContextClass_Initialize				();

public:
	
	enum {
		EVENT_RESIZE,
		TOTAL_EVENTS,
	};

	//----------------------------------------------------------------//
	MOAIShader*				AffirmShader				( MOAILuaState& state, int idx ) const;
	MOAITexture*			AffirmTexture				( MOAILuaState& state, int idx ) const;
	MOAIImageTexture*		CreateImageTexture			() const;
	MOAIIndexBuffer*		CreateIndexBuffer			() const;
	MOAITexture2D*			CreateTexture2D				() const;
	MOAIVertexArray*		CreateVertexArray			() const;
	MOAIVertexBuffer*		CreateVertexBuffer			() const;
	MOAIVertexFormat*		CreateVertexFormat			() const;
	ZLMatrix4x4				GetNormToWndMtx				();
	ZLMatrix4x4				GetNormToWndMtx				( const ZLRect& wndRect );
	MOAIShader*				GetShaderPreset				( MOAIShaderPresetEnum preset ) const;
	size_t					GetTextureMemoryUsage		() const;
	MOAIVertexFormat*		GetVertexFormatPreset		( MOAIVertexFormatPresetEnum preset ) const;
	ZLMatrix4x4				GetWorldToWndMtx			();
	ZLMatrix4x4				GetWorldToWndMtx			( const ZLRect& wndRect );
	ZLMatrix4x4				GetWndToNormMtx				();
	ZLMatrix4x4				GetWndToNormMtx				( const ZLRect& wndRect );
	ZLMatrix4x4				GetWndToWorldMtx			();
	ZLMatrix4x4				GetWndToWorldMtx			( const ZLRect& wndRect );
							MOAIGfxMgr					();
							~MOAIGfxMgr					();
	void					PopState					();
	void					PushState					();
};

#endif
