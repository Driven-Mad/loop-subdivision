#pragma once

class Application
{
public:
    Application();

	void run(float DT);
	///\brief draw function to draw to screen all objects etc.
	void draw();
	///\brief update function to update any movement etc. for objects
	void update(float DT);
	///\brief input handler for the application
	void inputHandler();
	///\brief initalise openGL
	bool InitGL();

        
    ~Application();
};