#include "fzafx.h"
#include "afxdll.h"

HINSTANCE HInst;

void InitExtensionModule(HINSTANCE HInst)
{
    ::HInst = HInst;
    AFX_MANAGE_STATE(AfxGetModuleState());
    afxCurrentResourceHandle = ::HInst;
}

void TermExtensionModule()
{
}
