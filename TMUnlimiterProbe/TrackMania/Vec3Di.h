#pragma once

namespace TrackMania
{

	class Vec3Di
	{
	public:
						Vec3Di			()
		{

		}

						Vec3Di			( dword x, dword y, dword z )
		{
			X = x;
			Y = y;
			Z = z;
		}

						Vec3Di			( const Vec3Di& other )
		{
			*this = other;
		}

		Vec3Di&			operator=		( const Vec3Di& other )
		{
			X = other.X;
			Y = other.Y;
			Z = other.Z;
			return *this;
		}

		bool			operator==		( const Vec3Di& other ) const
		{
			return X == other.X &&
				   Y == other.Y &&
				   Z == other.Z;
		}

		bool			operator!=		( const Vec3Di& other ) const
		{
			return !(*this == other);
		}

		Vec3Di			operator+		( const Vec3Di& other ) const
		{
			return Vec3Di ( X + other.X, Y + other.Y, Z + other.Z );
		}

		Vec3Di			operator-		( const Vec3D& other ) const
		{
			return Vec3Di ( X - other.X, Y - other.Y, Z - other.Z );
		}

		dword			X;
		dword			Y;
		dword			Z;
	};

}
