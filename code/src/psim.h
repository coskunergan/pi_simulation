



#pragma pack(push, psim_H_Enter)
#pragma pack(1)



typedef double (*PSIM_GET_PARAM_)(int nSimIndex, char * key, char * name, char * paramName, int * status);
typedef double (*PSIM_GET_PARAM_W)(int nSimIndex, char * key, wchar_t * name, wchar_t * paramName, int * status); 

typedef int (*PSIM_GET_TEXTPARAM_)(int nSimIndex, char * key, char * name, char * paramName, char *szReturn, int *pnReturnLen, int * status);
typedef int (*PSIM_GET_TEXTPARAM_W)(int nSimIndex, char * key, wchar_t * name, wchar_t * paramName, wchar_t *szReturn, int *pnReturnLen, int * status);
typedef struct					//data field should be 32 bit in case of the CH.exe compiler aligment
{
	unsigned long ulID;			//this is always the same, in case the mistake caller
	unsigned long version;		//version number, should be backward compatible
	int size;					//sizeof(PSIM_GET_PARAM_STRUCT);
	char key[100];
	double totaltime;
	char reserved1[24];			//set to 0
	PSIM_GET_PARAM_ funcCallback;
	PSIM_GET_PARAM_W funcCallbackW;
	PSIM_GET_TEXTPARAM_ funcCallbackText;
	PSIM_GET_TEXTPARAM_W funcCallbackTextW;
	char reserved2[100];		//set to 0
} PSIM_GET_PARAM_STRUCT;


#ifdef _UNICODE
	#define GetPsimValue GetPsimValueW
#else
	#define GetPsimValue GetPsimValueA
#endif

inline double GetPsimValueA(int nThreadIndex, void * pAppPtr, char * szName, char * szParamName, int & nStatus)
{	
	nStatus = -1; // If the function succeeds, the value of nStatus will be 0.
	double fValue = 0.0;
	if(pAppPtr != NULL)
	{
		PSIM_GET_PARAM_STRUCT *pData = (PSIM_GET_PARAM_STRUCT *)pAppPtr;
		if( (pData->ulID == 0X793CD88A) )//&& (pData->version >= 10) && (pData->size >= sizeof(PSIM_GET_PARAM_STRUCT)) )
		{
			fValue = pData->funcCallback(nThreadIndex, pData->key, szName, szParamName, &nStatus);;
		}

		//fValue = GetPsimValue(reserved_ThreadIndex, reserved_AppPtr, szName, szParamName, &nStatus);
	}

	return fValue;

}

inline double GetPsimValueW(int nThreadIndex, void * pAppPtr, wchar_t * szName, wchar_t * szParamName, int & nStatus)
{	
	nStatus = -1; // If the function succeeds, the value of nStatus will be 0.
	double fValue = 0.0;
	if(pAppPtr != NULL)
	{
		PSIM_GET_PARAM_STRUCT *pData = (PSIM_GET_PARAM_STRUCT *)pAppPtr;
		if( (pData->ulID == 0X793CD88A) )//&& (pData->version >= 10) && (pData->size >= sizeof(PSIM_GET_PARAM_STRUCT)) )
		{
			fValue = pData->funcCallbackW(nThreadIndex, pData->key, szName, szParamName, &nStatus);
		}

		//fValue = GetPsimValue(reserved_ThreadIndex, reserved_AppPtr, szName, szParamName, &nStatus);
	}

	return fValue;

}

#ifdef _UNICODE
	#define GetPsimText GetPsimTextW
#else
	#define GetPsimText GetPsimTextA
#endif

inline int GetPsimTextA(int nThreadIndex, void * pAppPtr, char * szName, char * szParamName, char *szReturn, int *pnReturnLen, int & nStatus)
{	
	nStatus = -1; // If the function succeeds, the value of nStatus will be 0.
	int nResult = 0;
	if(pAppPtr != NULL)
	{
		PSIM_GET_PARAM_STRUCT *pData = (PSIM_GET_PARAM_STRUCT *)pAppPtr;
		if( (pData->ulID == 0X793CD88A) )//&& (pData->version >= 10) && (pData->size >= sizeof(PSIM_GET_PARAM_STRUCT)) )
		{
			nResult = pData->funcCallbackText(nThreadIndex, pData->key, szName, szParamName, szReturn, pnReturnLen, &nStatus);;
		}

		//fValue = GetPsimValue(reserved_ThreadIndex, reserved_AppPtr, szName, szParamName, &nStatus);
	}

	return nResult;

}

inline int GetPsimTextW(int nThreadIndex, void * pAppPtr, wchar_t * szName, wchar_t * szParamName, wchar_t *szReturn, int *pnReturnLen, int & nStatus)
{	
	nStatus = -1; // If the function succeeds, the value of nStatus will be 0.
	int nResult = 0;
	if(pAppPtr != NULL)
	{
		PSIM_GET_PARAM_STRUCT *pData = (PSIM_GET_PARAM_STRUCT *)pAppPtr;
		if( (pData->ulID == 0X793CD88A) )//&& (pData->version >= 10) && (pData->size >= sizeof(PSIM_GET_PARAM_STRUCT)) )
		{
			nResult = pData->funcCallbackTextW(nThreadIndex, pData->key, szName, szParamName, szReturn, pnReturnLen, &nStatus);
		}

		//fValue = GetPsimValue(reserved_ThreadIndex, reserved_AppPtr, szName, szParamName, &nStatus);
	}

	return nResult;

}


#pragma pack(pop,psim_H_Enter)



