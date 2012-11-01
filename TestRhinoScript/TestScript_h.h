

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Thu Nov 01 09:22:40 2012
 */
/* Compiler settings for .\TestScript.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __TestScript_h_h__
#define __TestScript_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITestScriptObject_FWD_DEFINED__
#define __ITestScriptObject_FWD_DEFINED__
typedef interface ITestScriptObject ITestScriptObject;
#endif 	/* __ITestScriptObject_FWD_DEFINED__ */


#ifndef __TestScriptObject_FWD_DEFINED__
#define __TestScriptObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class TestScriptObject TestScriptObject;
#else
typedef struct TestScriptObject TestScriptObject;
#endif /* __cplusplus */

#endif 	/* __TestScriptObject_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __TestScript_LIBRARY_DEFINED__
#define __TestScript_LIBRARY_DEFINED__

/* library TestScript */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TestScript;

#ifndef __ITestScriptObject_DISPINTERFACE_DEFINED__
#define __ITestScriptObject_DISPINTERFACE_DEFINED__

/* dispinterface ITestScriptObject */
/* [uuid] */ 


EXTERN_C const IID DIID_ITestScriptObject;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0C171EB5-71BE-4E8B-AD17-FAE2405AB502")
    ITestScriptObject : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ITestScriptObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITestScriptObject * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITestScriptObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITestScriptObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITestScriptObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITestScriptObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITestScriptObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITestScriptObject * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ITestScriptObjectVtbl;

    interface ITestScriptObject
    {
        CONST_VTBL struct ITestScriptObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITestScriptObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITestScriptObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITestScriptObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITestScriptObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITestScriptObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITestScriptObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITestScriptObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ITestScriptObject_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TestScriptObject;

#ifdef __cplusplus

class DECLSPEC_UUID("C9ADE40C-65B6-44AA-A60F-906AC7303150")
TestScriptObject;
#endif
#endif /* __TestScript_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


