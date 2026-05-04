#pragma once

#include <Common/Offsets.hpp>

class IMaterial {
public:

	const char* GetName( ) {
		return Call<const char*>( this, 0 );
	}

	const char* GetTextureGroupName( ) {
		return Call<const char*>( this, 1 );
	}

	void IncrementReferenceCount( ) {
		return Call<void>( this, 12 );
	}

};
