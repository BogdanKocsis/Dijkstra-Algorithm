#pragma once
class Node
{
public:
	Node(long index, long x, long y);
	~Node() = default;
	long Getindex() const;
	long GetX() const;
	long GetY() const;
	void SetX (long xCoord);
	void SetY(long yCoord);


private:
	long m_x, m_y, m_index;
};

