/*
 * Application.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: thallock
 */

#include <app/Application.h>

#include "index/FileManager.h"
#include "index/substring/SubstringIndex.h"
#include "index/StringsList.h"
#include "query/IndexEntry.h"
#include "utils/boost_file_utils.h"

Application::Application() {}
Application::~Application() {}

void Application::reset()
{
	get_file_mapper().clear();
	get_strings_list().clear();


	get_index_entry_cache().flush();

	delete_file(get_settings().get_base_dir());

	// need to clear caches as well...
}

Application& get_application()
{
	static Application *app;
	if (app == nullptr)
	{
		app = new Application();
	}
	return *app;
}
