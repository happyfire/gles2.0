

inline Matrix4::Matrix4(bool isIdentity)
{
	if(isIdentity)
	{
		makeIdentity();
	}
}

inline Matrix4::Matrix4(f32 data[])
{
	memcpy(m, data, sizeof(m));
}

inline Matrix4::Matrix4(const Matrix4 &rhs)
{
	memcpy(m, rhs.m, sizeof(m));
}

inline Matrix4& Matrix4::operator=(const Matrix4 &rhs)
{
	if (this==&rhs)
	{
		return *this;
	}

	memcpy(m, rhs.m, sizeof(m));

	return *this;
}

inline f32& Matrix4::operator[](int index)
{
	ESL_ASSERT(index>=0 && index<16);

	return m[index];
}

inline const f32& Matrix4::operator[](int index) const
{
	ESL_ASSERT(index>=0 && index<16);

	return m[index];
}

inline bool Matrix4::operator ==(const Matrix4 &rhs) const
{
	for (int i = 0; i < 16; ++i)
	{
		if (m[i] != rhs.m[i])
		{
			return false;
		}
	}

	return true;
}

inline bool Matrix4::operator !=(const Matrix4 &rhs) const
{
	return !(*this == rhs);
}

inline Matrix4 Matrix4::operator +(const Matrix4 &rhs) const
{
	Matrix4 temp;

	temp.m[0] = m[0]+rhs.m[0];
	temp.m[1] = m[1]+rhs.m[1];
	temp.m[2] = m[2]+rhs.m[2];
	temp.m[3] = m[3]+rhs.m[3];
	temp.m[4] = m[4]+rhs.m[4];
	temp.m[5] = m[5]+rhs.m[5];
	temp.m[6] = m[6]+rhs.m[6];
	temp.m[7] = m[7]+rhs.m[7];
	temp.m[8] = m[8]+rhs.m[8];
	temp.m[9] = m[9]+rhs.m[9];
	temp.m[10] = m[10]+rhs.m[10];
	temp.m[11] = m[11]+rhs.m[11];
	temp.m[12] = m[12]+rhs.m[12];
	temp.m[13] = m[13]+rhs.m[13];
	temp.m[14] = m[14]+rhs.m[14];
	temp.m[15] = m[15]+rhs.m[15];

	return temp;
}

inline Matrix4& Matrix4::operator +=(const Matrix4 &rhs)
{
	m[0]+=rhs.m[0];
	m[1]+=rhs.m[1];
	m[2]+=rhs.m[2];
	m[3]+=rhs.m[3];
	m[4]+=rhs.m[4];
	m[5]+=rhs.m[5];
	m[6]+=rhs.m[6];
	m[7]+=rhs.m[7];
	m[8]+=rhs.m[8];
	m[9]+=rhs.m[9];
	m[10]+=rhs.m[10];
	m[11]+=rhs.m[11];
	m[12]+=rhs.m[12];
	m[13]+=rhs.m[13];
	m[14]+=rhs.m[14];
	m[15]+=rhs.m[15];

	return *this;
}

inline Matrix4 Matrix4::operator -(const Matrix4 &rhs) const
{
	Matrix4 temp;

	temp.m[0] = m[0]-rhs.m[0];
	temp.m[1] = m[1]-rhs.m[1];
	temp.m[2] = m[2]-rhs.m[2];
	temp.m[3] = m[3]-rhs.m[3];
	temp.m[4] = m[4]-rhs.m[4];
	temp.m[5] = m[5]-rhs.m[5];
	temp.m[6] = m[6]-rhs.m[6];
	temp.m[7] = m[7]-rhs.m[7];
	temp.m[8] = m[8]-rhs.m[8];
	temp.m[9] = m[9]-rhs.m[9];
	temp.m[10] = m[10]-rhs.m[10];
	temp.m[11] = m[11]-rhs.m[11];
	temp.m[12] = m[12]-rhs.m[12];
	temp.m[13] = m[13]-rhs.m[13];
	temp.m[14] = m[14]-rhs.m[14];
	temp.m[15] = m[15]-rhs.m[15];

	return temp;
}

inline Matrix4& Matrix4::operator -=(const Matrix4 &rhs)
{
	m[0]-=rhs.m[0];
	m[1]-=rhs.m[1];
	m[2]-=rhs.m[2];
	m[3]-=rhs.m[3];
	m[4]-=rhs.m[4];
	m[5]-=rhs.m[5];
	m[6]-=rhs.m[6];
	m[7]-=rhs.m[7];
	m[8]-=rhs.m[8];
	m[9]-=rhs.m[9];
	m[10]-=rhs.m[10];
	m[11]-=rhs.m[11];
	m[12]-=rhs.m[12];
	m[13]-=rhs.m[13];
	m[14]-=rhs.m[14];
	m[15]-=rhs.m[15];

	return *this;
}

inline Matrix4 Matrix4::operator *(f32 a) const
{
	Matrix4 temp;

	temp.m[0] = m[0]*a;
	temp.m[1] = m[1]*a;
	temp.m[2] = m[2]*a;
	temp.m[3] = m[3]*a;
	temp.m[4] = m[4]*a;
	temp.m[5] = m[5]*a;
	temp.m[6] = m[6]*a;
	temp.m[7] = m[7]*a;
	temp.m[8] = m[8]*a;
	temp.m[9] = m[9]*a;
	temp.m[10] = m[10]*a;
	temp.m[11] = m[11]*a;
	temp.m[12] = m[12]*a;
	temp.m[13] = m[13]*a;
	temp.m[14] = m[14]*a;
	temp.m[15] = m[15]*a;

	return temp;
}

inline Matrix4& Matrix4::operator *=(f32 a)
{
	m[0]*=a;
	m[1]*=a;
	m[2]*=a;
	m[3]*=a;
	m[4]*=a;
	m[5]*=a;
	m[6]*=a;
	m[7]*=a;
	m[8]*=a;
	m[9]*=a;
	m[10]*=a;
	m[11]*=a;
	m[12]*=a;
	m[13]*=a;
	m[14]*=a;
	m[15]*=a;

	return *this;
}

inline Matrix4& Matrix4::makeByMultiply(const Matrix4 &mat1, const Matrix4 &mat2)
{
	const f32 *m1 = mat1.m;
	const f32 *m2 = mat2.m;

	m[0] = m1[0]*m2[0] + m1[4]*m2[1] + m1[8]*m2[2] + m1[12]*m2[3];
	m[1] = m1[1]*m2[0] + m1[5]*m2[1] + m1[9]*m2[2] + m1[13]*m2[3];
	m[2] = m1[2]*m2[0] + m1[6]*m2[1] + m1[10]*m2[2] + m1[14]*m2[3];
	m[3] = m1[3]*m2[0] + m1[7]*m2[1] + m1[11]*m2[2] + m1[15]*m2[3];

	m[4] = m1[0]*m2[4] + m1[4]*m2[5] + m1[8]*m2[6] + m1[12]*m2[7];
	m[5] = m1[1]*m2[4] + m1[5]*m2[5] + m1[9]*m2[6] + m1[13]*m2[7];
	m[6] = m1[2]*m2[4] + m1[6]*m2[5] + m1[10]*m2[6] + m1[14]*m2[7];
	m[7] = m1[3]*m2[4] + m1[7]*m2[5] + m1[11]*m2[6] + m1[15]*m2[7];

	m[8] = m1[0]*m2[8] + m1[4]*m2[9] + m1[8]*m2[10] + m1[12]*m2[11];
	m[9] = m1[1]*m2[8] + m1[5]*m2[9] + m1[9]*m2[10] + m1[13]*m2[11];
	m[10] = m1[2]*m2[8] + m1[6]*m2[9] + m1[10]*m2[10] + m1[14]*m2[11];
	m[11] = m1[3]*m2[8] + m1[7]*m2[9] + m1[11]*m2[10] + m1[15]*m2[11];

	m[12] = m1[0]*m2[12] + m1[4]*m2[13] + m1[8]*m2[14] + m1[12]*m2[15];
	m[13] = m1[1]*m2[12] + m1[5]*m2[13] + m1[9]*m2[14] + m1[13]*m2[15];
	m[14] = m1[2]*m2[12] + m1[6]*m2[13] + m1[10]*m2[14] + m1[14]*m2[15];
	m[15] = m1[3]*m2[12] + m1[7]*m2[13] + m1[11]*m2[14] + m1[15]*m2[15];

	return *this;
}

inline Matrix4 Matrix4::operator *(const Matrix4 &rhs) const
{
	Matrix4 temp;
    
    multiplyMatrix(*this, rhs, temp);

	return temp;
}

inline Matrix4& Matrix4::operator *=(const Matrix4 &rhs)
{
	Matrix4 temp ( *this );
	return makeByMultiply( temp, rhs );
}

inline Matrix4& Matrix4::makeIdentity()
{
	memset(m, 0, 16*sizeof(f32));
	m[0] = m[5] = m[10] = m[15] = 1.0f;

	return *this;
}

inline Matrix4& Matrix4::makeTranslationMatrix(f32 x, f32 y, f32 z)
{
	makeIdentity();
	m[12] = x;
	m[13] = y;
	m[14] = z;
	return *this;
}

inline Matrix4& Matrix4::setTranslation(const Vector3 &translation)
{
    m[12] = translation.x;
	m[13] = translation.y;
	m[14] = translation.z;
	return *this;
}

inline Matrix4& Matrix4::setTranslation(f32 x, f32 y, f32 z)
{
	m[12] = x;
	m[13] = y;
	m[14] = z;
	return *this;
}

inline Vector3 Matrix4::getTranslation() const
{
	return Vector3(m[12],m[13],m[14]);
}

inline Matrix4& Matrix4::postScale(const Vector3 &scale)
{
    m[0] *= scale.x;
    m[1] *= scale.x;
    m[2] *= scale.x;
    m[4] *= scale.y;
    m[5] *= scale.y;
    m[6] *= scale.y;
    m[8] *= scale.z;
    m[9] *= scale.z;
    m[10] *= scale.z;
    return *this;
}

inline Matrix4& Matrix4::makeScaleMatrix(f32 sx, f32 sy, f32 sz)
{
	makeIdentity();
	m[0] = sx;
	m[5] = sy;
	m[10] = sz;
	return *this;
}

inline Matrix4& Matrix4::makeRotateXMatrix(f32 rotDegree)
{
	float radian = degreeToRadian(rotDegree);

	makeIdentity();

	m[5] = cosf(radian);
	m[6] = -sinf(radian);
	m[9] = -m[6];
	m[10] = m[5];

	return *this;
}

inline Matrix4& Matrix4::makeRotateYMatrix(f32 rotDegree)
{
	float radian = degreeToRadian(rotDegree);

	makeIdentity();

	m[0] = cosf(radian);
	m[2] = sinf(radian);
	m[8] = -m[2];
	m[10] = m[0];

	return *this;
}

inline Matrix4& Matrix4::makeRotateZMatrix(f32 rotDegree)
{
	float radian = degreeToRadian(rotDegree);

	makeIdentity();

	m[0] = cosf(radian);
	m[1] = sinf(radian);
	m[4] = -m[1];
	m[5] = m[0];

	return *this;
}

inline Matrix4& Matrix4::makePerspectiveProjectionMatrix(f32 fovAngle, f32 nearPlane, f32 farPlane, f32 aspect)
{
	float size = nearPlane * tanf(degreeToRadian(fovAngle) / 2.0f);
	float left = -size, right = size, bottom = -size / aspect, top = size / aspect;

	// Unused values in perspective formula.
	m[1] = m[2] = m[3] = m[4] = 0;
	m[6] = m[7] = m[12] = m[13] = m[15] = 0;

	// Perspective formula.
	m[0] = 2 * nearPlane / (right - left);
	m[5] = 2 * nearPlane / (top - bottom);
	m[8] = (right + left) / (right - left);
	m[9] = (top + bottom) / (top - bottom);
	m[10] = -(farPlane + nearPlane) / (farPlane - nearPlane);
	m[11] = -1;
	m[14] = -(2 * farPlane * nearPlane) / (farPlane - nearPlane);

	return *this;
}

inline const f32* Matrix4::getData() const 
{ 
	return m; 
}

inline f32* Matrix4::getData() 
{ 
	return m;
}

inline Matrix4 operator*(f32 a, const Matrix4 &m)
{
	Matrix4 temp;

	temp.m[0] = m[0]*a;
	temp.m[1] = m[1]*a;
	temp.m[2] = m[2]*a;
	temp.m[3] = m[3]*a;
	temp.m[4] = m[4]*a;
	temp.m[5] = m[5]*a;
	temp.m[6] = m[6]*a;
	temp.m[7] = m[7]*a;
	temp.m[8] = m[8]*a;
	temp.m[9] = m[9]*a;
	temp.m[10] = m[10]*a;
	temp.m[11] = m[11]*a;
	temp.m[12] = m[12]*a;
	temp.m[13] = m[13]*a;
	temp.m[14] = m[14]*a;
	temp.m[15] = m[15]*a;

	return temp;

}

inline void multiplyMatrix(const Matrix4& mat1, const Matrix4& mat2, Matrix4& matOut)
{
	const f32 *m1 = mat1.getData();
	const f32 *m2 = mat2.getData();
    
	matOut.m[0] = m1[0]*m2[0] + m1[4]*m2[1] + m1[8]*m2[2] + m1[12]*m2[3];
	matOut.m[1] = m1[1]*m2[0] + m1[5]*m2[1] + m1[9]*m2[2] + m1[13]*m2[3];
	matOut.m[2] = m1[2]*m2[0] + m1[6]*m2[1] + m1[10]*m2[2] + m1[14]*m2[3];
	matOut.m[3] = m1[3]*m2[0] + m1[7]*m2[1] + m1[11]*m2[2] + m1[15]*m2[3];
    
	matOut.m[4] = m1[0]*m2[4] + m1[4]*m2[5] + m1[8]*m2[6] + m1[12]*m2[7];
	matOut.m[5] = m1[1]*m2[4] + m1[5]*m2[5] + m1[9]*m2[6] + m1[13]*m2[7];
	matOut.m[6] = m1[2]*m2[4] + m1[6]*m2[5] + m1[10]*m2[6] + m1[14]*m2[7];
	matOut.m[7] = m1[3]*m2[4] + m1[7]*m2[5] + m1[11]*m2[6] + m1[15]*m2[7];
    
	matOut.m[8] = m1[0]*m2[8] + m1[4]*m2[9] + m1[8]*m2[10] + m1[12]*m2[11];
	matOut.m[9] = m1[1]*m2[8] + m1[5]*m2[9] + m1[9]*m2[10] + m1[13]*m2[11];
	matOut.m[10] = m1[2]*m2[8] + m1[6]*m2[9] + m1[10]*m2[10] + m1[14]*m2[11];
	matOut.m[11] = m1[3]*m2[8] + m1[7]*m2[9] + m1[11]*m2[10] + m1[15]*m2[11];
    
	matOut.m[12] = m1[0]*m2[12] + m1[4]*m2[13] + m1[8]*m2[14] + m1[12]*m2[15];
	matOut.m[13] = m1[1]*m2[12] + m1[5]*m2[13] + m1[9]*m2[14] + m1[13]*m2[15];
	matOut.m[14] = m1[2]*m2[12] + m1[6]*m2[13] + m1[10]*m2[14] + m1[14]*m2[15];
	matOut.m[15] = m1[3]*m2[12] + m1[7]*m2[13] + m1[11]*m2[14] + m1[15]*m2[15];
}

