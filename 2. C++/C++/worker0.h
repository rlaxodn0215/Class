#pragma once
#include<string>
#include<iostream>

using namespace std;
class Worker
{
private:
	std::string fullname;
	long id;
protected:
	virtual void Data() const;
	virtual void Get();
public:
	Worker() :fullname("no name"), id(0L) { }
	Worker(const std::string & s, long n):fullname(s),id(n){  }
	virtual ~Worker();
	virtual void Set() {};
	virtual void Show() const {};

};

class Waiter : virtual public Worker
{
private:
	int panache;
protected:
	void Data() const;
	void Get();
public:
	Waiter():Worker(),panache(0){  }
	Waiter(const std::string & s, long n,int p=0):Worker(s,n),panache(p){  }
	Waiter(const Worker &wk,int p=0): Worker(wk),panache(p){  }
	virtual ~Waiter() { };
	void Set();
	void Show() const;
};

class Signer : virtual public Worker
{
protected:
	enum {other, alto, contralto,soprano,bass,baritone,tenor};
	enum { Vtypes = 7 };
	void Data() const;
	void Get();
private:
	const static char* pv[Vtypes];
	int voice;
public:
	Signer():Worker(),voice(other){ }
	Signer(const std::string & s, long n,int v=other):Worker(s,n),voice(v){  }
	Signer(const Worker &wk,int v =other):Worker(wk),voice(v){ }
	virtual ~Signer(){}
	void Set();
	void Show() const;
};

class SigningWaiter : public Signer, public Waiter
{
protected:
	void Data() const;
	void Get();
public:
	SigningWaiter() { }
	SigningWaiter(const std::string & s, long n,int p=0,int v=other)
		:Worker(s,n),Waiter(s,n,p),Signer(s,n,v){}
	SigningWaiter(const Worker & wk,int p=0,int v=other)
		:Worker(wk),Waiter(wk,p),Signer(wk, v){}
	SigningWaiter(const Signer&wt,int p=0): Worker(wt),Waiter(wt,p),Signer(wt){ }
		~SigningWaiter() {}
	void Set();
	void Show() const;
};
