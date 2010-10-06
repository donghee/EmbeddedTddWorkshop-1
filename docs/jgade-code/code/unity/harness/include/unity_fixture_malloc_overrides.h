/*
 * unity_fixture_malloc_overrides.h
 *
 *  Created on: Sep 6, 2010
 *      Author: james
 */

#ifndef UNITY_FIXTURE_MALLOC_OVERRIDES_H_
#define UNITY_FIXTURE_MALLOC_OVERRIDES_H_

#define malloc unity_malloc
#define calloc unity_calloc
#define realloc unity_realloc
#define free unity_free

#endif /* UNITY_FIXTURE_MALLOC_OVERRIDES_H_ */
