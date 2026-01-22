#include "Tribe.h"

int compareSurvivorDifferentAddress( Survivor* s1, Survivor* s2 )
{
	if( s1 == s2 || s1 == NULL || s2 == NULL )
		return 0;
	
	if( s1->name == s2->name )
		return 0; 
	
	if( strcmp( s1->name, s2->name ) != 0 )
		return 0;

	if( s1->age != s2->age )
		return 0;

	if( s1->followers != s2->followers )
		return 0;

	return 1;
}

int compareTribeDifferentAddress( Tribe* t1, Tribe* t2 )
{
	int i;

	if( t1 == t2 || t1 == NULL || t2 == NULL )
		return 0;

	if( t1->name == t2->name )
		return 0;

	if( strcmp( t1->name, t2->name ) != 0 )
		return 0;

	if( t1->bandana_color == t2->bandana_color )
		return 0;

	if( strcmp( t1->bandana_color, t2->bandana_color ) != 0 )
		return 0;

	if( t1->num_of_survivors != t2->num_of_survivors )
		return 0;

	if( t1->survivors == t2->survivors )
		return 0;

	for( i = 0; i < t1->num_of_survivors; ++i )
	{
		if( 0 == compareSurvivorDifferentAddress( t1->survivors[i], t2->survivors[i] ) )
			return 0;
	}

	return 1;
}

int checkSurvivor( Tribe* t, Survivor* s )
{
	int i;
	if( NULL == t || NULL == s )
		return 0;

	for( i = 0; i < t->num_of_survivors; ++i )
	{
		if( 0 == strcmp( t->survivors[i]->name, s->name )
			&& t->survivors[i]->age == s->age
			&& t->survivors[i]->followers == s->followers )
			return 1;
	}

	return 0;
}

int checkSortedByAgesArray( Tribe* t, float ages[] )
{
	int i;
	for( i = 0; i < t->num_of_survivors; ++i )
	{
		if( t->survivors[i]->age != ages[i] )
			return 0;
	}

	return 1;
}

int main()
{
	int sum = 0;
	float age1 = 26.f, age2 = 56.f, age3 = 21.5f, age4 = 38.5f;
	float arr1[] = { age3, age1, age4, age2 };
	float arr2[] = { age3, age2, age4, age1 };
	Survivor s1 = { "Moshe Moshkovitz", age1, 30 };
	Survivor s2 = { "David Davidian", age2, 25 };
	Survivor s3 = { "Azzam Azzam", age3, 32 };
	Survivor s4 = { "Eli Eliyahu", age4, 20 };
	Survivor* pItem[3] = { &s1, &s2, &s3 };
	Survivor* pItem2[4] = { &s1, &s2, &s3, &s4 };
	Tribe t = { pItem, 3, "Sunrise", "Blue" };
	Tribe t2 = { pItem2, 4, "Sunset", "Orange" };
	Tribe* tmpTribe = NULL;
	Tribe* myTribe;
	Survivor* p1;
	Survivor* p2;

	//------------------------------------------------------------------------------------------------------------
	//=============== EX 1 ================// 
	p1 = CreateSurvivor( "Moshe Moshkovitz", age1, 30 );
	if( 0 == compareSurvivorDifferentAddress( p1, &s1 ) )
		printf( "Failed Ex1 - CreateNewSurvivor function (-8)\n" );

	//=============== EX 2 ================// 
	p2 = DuplicateSurvivor( &s2 );
	if( 0 == compareSurvivorDifferentAddress( p2, &s2 ) )
		printf( "Failed Ex2 - DuplicateSurvivor function (-8)\n" );

	//=============== EX 3 ================// 
	tmpTribe = AddSurvivor( tmpTribe, &s1 );
	if( 0 == checkSurvivor( tmpTribe, &s1 ) )
		printf( "Failed Ex3 - AddSurvivor function (-8)\n" );

	//=============== EX 4 ================// 
	myTribe = DuplicateTribe( &t );
	if( 0 == compareTribeDifferentAddress( &t, myTribe ) )
		printf( "Failed Ex4 - DuplicateTribe function (-8)\n" );

	//=============== EX 5 ================// 
	SortByAge( &t2 );
	if( 0 == checkSortedByAgesArray( &t2, arr1 ) )
		printf( "Failed Ex5 - SortByAge function (-8)\n" );

	//=============== EX 6 ================// 
	SortByName( &t2 );
	if( 0 == checkSortedByAgesArray( &t2, arr2 ) )
		printf( "Failed Ex6 - SortByName function (-8)\n" );

	//=============== EX 7 ================// 
	sum = TotalFollowers( &t2 );
	if( sum != 107 )
		printf( "Failed Ex7 - TotalFollowers function (-8)\n" );

	//=============== EX 8 ================// 
	if( 1 != UpdateFollowers( &t2, "Azzam Azzam", 10 ) )
		printf( "Failed Ex8 - UpdateFollowers function (-8)\n" );
	else if( t2.survivors[0]->followers != 42 )
		printf( "Failed Ex8 - UpdateFollowers function (-8)\n" );

	//=============== EX 9 ================// 
	if( 0 != UpdateAge( &t2, "lala", 4.5 ) )
		printf( "Failed Ex9 - UpdateAge function (-8)\n" );

	//=============== EX 10 ================// 
	if( 20 != GetSurvivorFollowers( &t2, "Eli Eliyahu" ) )
		printf( "Failed Ex10 - GetSurvivorFollowers function (-8)\n" );

	//=============== EX 11+12 ================// 
	FreeTribe( myTribe );
	
	//=============== FINISH ================// 
	printf( "\n\ndone\n" );

	return 0;
}