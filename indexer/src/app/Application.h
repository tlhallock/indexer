/*
 * Application.h
 *
 *  Created on: Jun 11, 2014
 *      Author: thallock
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

class Application
{
public:
	Application();
	virtual ~Application();

	void reset();
};

Application &get_application();

#endif /* APPLICATION_H_ */
