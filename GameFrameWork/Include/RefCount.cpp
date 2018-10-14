#include "RefCount.h"

//�����ϴϱ� �ϴ� 1
RefCount::RefCount() 
	: m_RefCount(1), isShow(true), isActiv(true)
{
}

RefCount::~RefCount()
{
}

int RefCount::Release()
{
	m_RefCount--;
	
	if (m_RefCount == 0)
	{
		delete this;
		return NULL;
	}
	return m_RefCount;
}
