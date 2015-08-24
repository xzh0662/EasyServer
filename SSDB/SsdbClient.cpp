/*
 * SsdbClient.cpp
 *
 *  Created on: Aug 22, 2015
 *      Author: root
 */

#include "SsdbClient.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

inline static
Status _read_str(const std::vector<std::string> *resp, std::string *ret){
	Status s(resp);
	if(s.ok()){
		if(resp->size() >= 2){
			*ret = resp->at(1);
		}else{
			return Status("server_error");
		}
	}
	return s;
}

SsdbClient::SsdbClient(void)
	: needDataSize_(0)
{
	recvBuf_ = new Buffer();
}

SsdbClient::~SsdbClient(void)
{

}

int SsdbClient::receive(int fd, Buffer *buffer)
{
	if (super::receive(fd, buffer) != 0 )
	{
		return -1;
	}

	printf("SsdbClient::receive len %d\n", (int)buffer->Length());

	this->recvBuf_->move(buffer);

	while((int)this->recvBuf_->Length() > this->needDataSize_)
	{
		if (this->needDataSize_ == 0)
		{
			size_t outLen;
			char* recvLine = this->recvBuf_->readLine(&outLen);
			if (!recvLine)
			{
				break;
			}
			if (outLen == 0)
			{
				int resLen = this->oneRes_.size();
				if (resLen > 0)
				{
					//this complete handle

//					for(int i = 0; i < resLen; ++i)
//					{
//						printf("%s\n", this->oneRes_[i].c_str());
//					}

					std::string retStr;
					Status s = _read_str(&this->oneRes_, &retStr);
					printf("complete len %d ok %d\n", resLen, s.ok());
					if(s.ok())
					{
						printf("retStr = %s\n", retStr.c_str());
					}
					else
					{
						printf("%s\n", s.code().c_str());
					}
				}

				this->oneRes_.clear();
			}
			else
			{
				this->needDataSize_ = atoi(recvLine);
				free(recvLine);
			}
		}
		else
		{
			char *data = (char *)malloc(this->needDataSize_ + 1);
			memset(data, '\0', this->needDataSize_ + 1);
			this->recvBuf_->removeData((void *)data, (size_t)this->needDataSize_);
			this->oneRes_.push_back(data);
			free(data);
			if (this->recvBuf_->deleteLineEnd() != 0)
			{
				printf("ssdb msg error\n");
			}
			this->needDataSize_ = 0;
		}
	}
	return 0;
}


void SsdbClient::get(const std::string &key)
{
	std::vector<std::string> req;
	req.push_back("get");
	req.push_back(key);

	this->request(req);
}

void SsdbClient::request(const std::vector<std::string> &req)
{
	Buffer *buf;
	BUFFER_NEW(buf, 1024 * 10);

	int reqVecLen = req.size();
	for (int i = 0; i < reqVecLen; ++i)
	{
		int reqLen = req[i].size();
		char len[16];
		int num = snprintf(len, sizeof(len), "%d\n", reqLen);
		buf->addData(len, num);
		buf->addData(req[i].c_str(), reqLen);
		buf->addData("\n", 1);
	}

	buf->addData("\n", 1);

	this->send(-1, buf);
}

