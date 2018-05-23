#pragma once

class Model{
private:
	int id;
	char* data = nullptr;
	size_t size = 0;

public:
	Model();
	Model(size_t s);
	Model(const Model& m);
	~Model();

public:
	Model& operator=(const Model& m);
	Model(Model&& other);
	Model& operator=(Model&& other);

public:
	void Show() const;
	int getSize()const;

public:
	bool operator==(const Model& other)const;
	bool operator < (const Model& rhs)const;

};

