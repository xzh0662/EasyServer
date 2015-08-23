/*
 * SsdbClient.h
 *
 *  Created on: Aug 22, 2015
 *      Author: root
 */

#ifndef SSDBCLIENT_H_
#define SSDBCLIENT_H_

#include "TcpClient.h"
#include <vector>
#include <string>
#include "Buffer.h"

using namespace Easy;

class Status{
public:
	/**
	 * Returns <code>true</code> if the request succeeded.
	 */
	bool ok(){
		return code_ == "ok";
	}
	/**
	 * Returns <code>true</code> if the requested key is not found. When this method
	 * returns <code>true</code>, ok() will always returns <code>false</code>.
	 */
	bool not_found(){
		return code_ == "not_found";
	}
	/**
	 * Returns <code>true</code> if error occurs during the request.
	 * It might be a server error, or a client error.
	 */
	bool error(){
		return code_ != "ok";
	}
	/**
	 * The response code.
	 */
	std::string code(){
		return code_;
	}

	Status(){}
	Status(const std::string &code){
		code_ = code;
	}
	Status(const std::vector<std::string> *resp){
		if(resp && resp->size() > 0){
			code_ = resp->at(0);
		}else{
			code_ = "error";
		}
	}
private:
	std::string code_;
};

class SsdbClient : public TcpClient
{
	typedef TcpClient super;
public:
	SsdbClient(void);
	virtual ~SsdbClient(void);

	virtual int receive(int fd, Buffer *buffer);

	void get(const std::string &key);

private:
	void request(const std::vector<std::string> &req);
	Buffer* recvBuf_;
	std::vector<std::string> oneRes_;
	int needDataSize_;
};



#endif /* SSDBCLIENT_H_ */
