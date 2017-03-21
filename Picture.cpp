#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>


template <typename T>
class ArrayList
{
	T* data;
	int _size, _maxSize;
public:
	ArrayList(int maxsize){data = new T[maxsize]; _maxSize = maxsize; _size = 0;}
	ArrayList(){data = new T[50]; maxSize = 50; size = 0;}
	~ArrayList(){delete data;}
	int size(){return _size;}
	int maxSize(){return _maxSize;}
	void push(T n){data[size++] = n;}
	void operator+(T n){push(n);}
	T* Data(){return data;}
	T& operator[](int i){return data[i];}
	void resize(int nsize);
};

float FRAME_DELAY;
struct Vector2
{
	float x,y;
	//operators
	Vector2(float, float);
	Vector2();
	Vector2 operator+(Vector2);
	Vector2 operator-(Vector2);
	Vector2 operator*(float);
	Vector2 operator/(float);

	Vector2 operator+=(Vector2);
	Vector2 operator-=(Vector2);
	Vector2 operator*=(float);
	Vector2 operator/=(float);

	bool operator==(Vector2);

	float sqrMag();
	float Mag();
};

struct ColorRGB
{
	unsigned char r,g,b;
	ColorRGB():r(0), g(0), b(0){}
	ColorRGB(char _r, char _g, char _b):r(_r),g(_g), b(_b){}
	char *toCData(){char ret[3]; ret[] return ret;}
};

char *ColorArrayToCharPointer(ColorRGB d[], int length)
{
	ArrayList<char> ret(length*3);
	for (int i = 0; i < length; ++i)
	{
		char *a= d[i].toCData();
	}
	return ret.Data();
}

void initGlut(const char*, int*, char**, Vector2, float);
void drawRect(Vector2, Vector2, ColorRGB);
void drawCircle(Vector2, float, ColorRGB);
void drawCircle(Vector2, float, float, ColorRGB);

Vector2::Vector2(float _x, float _y):x(_x), y(_y){}
Vector2::Vector2():x(0),y(0){}

Vector2 Vector2::operator+(Vector2 other)
{
	return Vector2(x+other.x, y+other.y);
}
Vector2 Vector2::operator-(Vector2 other)
{
	return Vector2(x-other.x, y-other.y);
}
Vector2 Vector2::operator*(float scalar)
{
	return Vector2(x*scalar, y*scalar);
}
Vector2 Vector2::operator/(float scalar)
{
	return Vector2(x/scalar, y/scalar);
}

Vector2 Vector2::operator+=(Vector2 other)
{
	x+=other.x; y+=other.y;
	//std::cout << x,y;
	return *this;
}
Vector2 Vector2::operator-=(Vector2 other)
{
	x-=other.x; y-=other.y;
	return *this;
}
Vector2 Vector2::operator*=(float scalar)
{
	x*=scalar; y*=scalar;
	return *this;
}
Vector2 Vector2::operator/=(float scalar)
{
	x/=scalar; y/=scalar;
	return *this;
}

bool Vector2::operator==(Vector2 o)
{
	return x==o.x && y==o.y;
}

float Vector2::sqrMag()
{
	return x*x + y*y;
}

float Vector2::Mag()
{
	return sqrt(sqrMag());
}

Vector2 operator*(float l,Vector2 r){return r*l;}
Vector2 operator/(float l,Vector2 r){return r/l;}

struct Vector3
{
	float x,y,z;
};

GLuint testtxt;

void Render(int)
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glutSwapBuffers();
	glutTimerFunc( FRAME_DELAY, Render, 0 );
}

void Display()
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
	glutTimerFunc( FRAME_DELAY, Render, 0 );
}

void initGlut(const char* name, int* argc, char** argv ,Vector2 size = Vector2(1280,720), float FrameRate = 1000./60.)
{
	glutInit(argc, argv);
	glutInitWindowSize(size.x, size.y);
	glutCreateWindow(name);
	glutDisplayFunc(Display);
	glutMouseFunc(NULL);

	glutPassiveMotionFunc(NULL);
	glutMotionFunc(NULL);

	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	glViewport( 0.0, 0.0, size.x, size.y );
	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();	
	
	
	
	glOrtho( 0.0, size.x, size.y, 0.0, 100000000, -100000000 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	FRAME_DELAY = FrameRate;

	glGenTextures(1,&testtxt);
	glBindTexture(GL_TEXTURE_2D, testtxt);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

int main(int argc, char *argv[])
{
	initGlut("Testing Images",&argc, argv, Vector2(500,500));

	glutMainLoop();
	return 0;
}