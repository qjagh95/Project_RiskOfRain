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
	string m_Tag;	///내가 뭔지.. 이름을 지어주기위함
	int m_RefCount;
	bool isShow;	///활성 비활성모드
	bool isActiv;   ///객체 생성됬나 안됬나 기능

};

