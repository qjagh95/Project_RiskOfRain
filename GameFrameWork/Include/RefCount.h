#pragma once
#include "stdafx.h"

class RefCount
{
public:
	RefCount();
	virtual ~RefCount() = 0;

	void SetTag(const string& TagName) { m_Tag = TagName; }
	const string& GetTag() const { return m_Tag; }
	void AddRefCount() { m_RefCount++; }
	int GetRefCount() const { return m_RefCount; }

	bool GetisShow() const { return isShow; }
	bool GetisActiv() const { return isActiv; }
	void SetisShow(bool Value) { isShow = Value; }
	void SetisActiv(bool Value) { isActiv = Value; }
	void SetRefCount(int Value) { m_RefCount = Value; }
	int Release();

protected:
	string m_Tag;	///���� ����.. �̸��� �����ֱ�����
	int m_RefCount;
	bool isShow;	///Ȱ�� ��Ȱ�����
	bool isActiv;   ///��ü �����糪 �ȉ糪 ���

};

