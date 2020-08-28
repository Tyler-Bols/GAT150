#include "pch.h"
#include "Transform.h"

namespace nc
{

	std::istream& operator>>(std::istream& stream, Transform& transform)
	{
		stream >> transform.position;

		std::string line;
		std::getline(stream, line);
		transform.scale = stof(line);

		std::getline(stream, line);
		transform.angle = stof(line);

		return stream;
	}
	void Transform::Update()
	{
		Matrix33 mxS;
		Matrix33 mxR;
		Matrix33 mxT;

		mxS.Scale(scale);
		mxR.Rotate(angle);
		mxT.Translate(position);

		matrix = mxS * mxR * mxT;


	}
	void Transform::Update(const Matrix33& mx)
	{
		Matrix33 mxS;
		Matrix33 mxR;
		Matrix33 mxT;

		mxS.Scale(scale);
		mxR.Rotate(angle);
		mxT.Translate(position);

		matrix = mxS * mxR * mxT * mx;
	}
}