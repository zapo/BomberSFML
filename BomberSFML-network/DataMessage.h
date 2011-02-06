/*
 * DataMessage.h
 *
 *  Created on: 2011-01-31
 *      Author: zapo
 */

#ifndef DATAMESSAGE_H_
#define DATAMESSAGE_H_

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <sstream>

namespace Bomber {

template <typename T>
class DataMessage {
public:

	DataMessage() {

	}

	DataMessage(T &data) : data(&data) {

	}

	T& getData() {
		return *data;
	}

	void setData(T &data) {
		this->data = &data;
	}

	~DataMessage() {
	}

private:
	T *data;
};

}


using namespace Bomber;

template <typename T>
sf::Packet& operator<<(sf::Packet &p, DataMessage<T> &message) {

	std::ostringstream text_stream;
	boost::archive::text_oarchive archive(text_stream);
	T data = message.getData();

	archive << data;

	p << text_stream.str();

	return p;
}

template <typename T>
sf::Packet& operator>>(sf::Packet &p, DataMessage<T> &message) {


	std::string s_data;

	T *data = new T();

	p >> s_data;

	std::istringstream text_stream(s_data);

	boost::archive::text_iarchive archive(text_stream);
	archive >> *data;

	message.setData(*data);

	return p;

}




#endif /* DATAMESSAGE_H_ */
