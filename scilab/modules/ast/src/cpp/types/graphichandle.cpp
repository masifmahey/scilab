/*
*  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
*  Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
*
*  This file must be used under the terms of the CeCILL.
*  This source file is licensed as described in the file COPYING, which
*  you should have received as part of this distribution.  The terms
*  are also available at
*  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
*
*/

#include <sstream>
#include "graphichandle.hxx"
#include "tostring_common.hxx"
#include "overload.hxx"
#include "type_traits.hxx"

extern "C"
{
#include <stdio.h>
#include "localization.h"
#include "os_string.h"
#include "sci_malloc.h"
}

using namespace std;

namespace types
{
/*****************
 * GraphicHandle *
 *****************/
GraphicHandle::GraphicHandle(long long _handle)
{
    int piDims[2]   = {1, 1};
    long long* pH = NULL;
    create(piDims, 2, &pH, NULL);
    pH[0] = _handle;
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

GraphicHandle::GraphicHandle(int _iRows, int _iCols)
{
    int piDims[2]   = {_iRows, _iCols};
    long long* pH = NULL;
    create(piDims, 2, &pH, NULL);
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

GraphicHandle::GraphicHandle(int _iDims, int* _piDims)
{
    long long* pH = NULL;
    create(_piDims, _iDims, &pH, NULL);
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

void GraphicHandle::whoAmI()
{
    std::cout << "types::GraphicHandle";
}


GraphicHandle::~GraphicHandle()
{
    if (isDeletable() == true)
    {
        deleteAll();
    }
#ifndef NDEBUG
    Inspector::removeItem(this);
#endif
}

InternalType* GraphicHandle::clone()
{
    GraphicHandle* pGH = new GraphicHandle(getDims(), getDimsArray());
    for (int i = 0 ; i < getSize() ; i++)
    {
        pGH->set(i, get(i));
    }
    return pGH;
}

bool GraphicHandle::operator==(const InternalType& it)
{
    if (const_cast<InternalType &>(it).isBool() == false)
    {
        return false;
    }

    GraphicHandle* pGH = const_cast<InternalType &>(it).getAs<types::GraphicHandle>();

    if (pGH->getDims() != getDims())
    {
        return false;
    }

    for (int i = 0 ; i < getDims() ; i++)
    {
        if (pGH->getDimsArray()[i] != getDimsArray()[i])
        {
            return false;
        }
    }

    for (int i = 0 ; i < getSize() ; i++)
    {
        if (get(i) == pGH->get(i))
        {
            return false;
        }
    }
    return true;
}

bool GraphicHandle::operator!=(const InternalType& it)
{
    return !(*this == it);
}

bool GraphicHandle::subMatrixToString(std::wostringstream& /*ostr*/, int* /*_piDims*/, int /*_iDims*/)
{
    //call %h_p(h)
    //GraphicHandle* pTemp = new GraphicHandle(_iDims, _piDims);
    //long long* pHandle = pTemp->get();
    //for(int i = 0 ; i < pTemp->getSize() ; i++)
    //{
    //    pHandle[i] = 0;
    //}

    //typed_list in;
    //typed_list out;
    //in.push_back(pTemp);

    //InternalType* pIT = (InternalType*)context_get(L"%h_p");
    //if(pIT->isFunction())
    //{
    //    ast::ExecVisitor execCall;
    //    Function* pCall = (Function*)pIT;
    //    pCall->call(in, 1, out, &execCall);
    //}

    return true;
}

long long GraphicHandle::getNullValue()
{
    return 0;
}

GraphicHandle* GraphicHandle::createEmpty(int _iDims, int* _piDims, bool /*_bComplex*/)
{
    return new GraphicHandle(_iDims, _piDims);
}

long long GraphicHandle::copyValue(long long _hanlde)
{
    return _hanlde;
}

void GraphicHandle::deleteAll()
{
    delete[] m_pRealData;
    m_pRealData = NULL;
    deleteImg();
}

void GraphicHandle::deleteImg()
{
}

long long* GraphicHandle::allocData(int _iSize)
{
    return new long long[_iSize];
}

bool GraphicHandle::invoke(typed_list & in, optional_list & opt, int _iRetCount, typed_list & out, ast::ConstVisitor & execFunc, const ast::Exp & e)
{
    if (in.size() == 0)
    {
        out.push_back(this);
    }
    else if (in.size() == 1 && in[0]->isString())
    {
        this->IncreaseRef();
        in.push_back(this);

        Overload::call(L"%h_e", in, 1, out, &execFunc);
    }
    else
    {
        return ArrayOf<long long>::invoke(in, opt, _iRetCount, out, execFunc, e);
    }

    return true;
}

bool GraphicHandle::transpose(InternalType *& out)
{
    return type_traits::transpose(*this, out);
}

}