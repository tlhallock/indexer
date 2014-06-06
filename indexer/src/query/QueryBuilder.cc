/*
 * QueryBuilder.cpp
 *
 *  Created on: Jun 3, 2014
 *      Author: thallock
 */

#include <query/QueryBuilder.h>

#include "include/export.h"

QueryBuilder::QueryBuilder() {}
QueryBuilder::~QueryBuilder()
{
}

Query* QueryBuilder::build_query(const char* string)
{
	if (!get_settings().should_index_substrings())
	{
		return new SuperStringQuery(get_strings_list().iterator(string), string);
	}

	int len = strlen(string);
	if (len < get_settings().get_minimum_substring_index())
	{
		// what to do?
		return nullptr;
	}

	if (len > get_settings().get_maximum_substring_index())
	{
		return new SuperStringQuery(get_exp_index().iterator(string), string);
	}

	return new SuperStringQuery(get_exp_index().iterator(string), string);
//	return new FileOffsetListQuery(string);
}

QueryBuilder& get_builder()
{
	static QueryBuilder *builder;
	if (builder == nullptr)
	{
		builder = new QueryBuilder();
	}
	return *builder;
}
