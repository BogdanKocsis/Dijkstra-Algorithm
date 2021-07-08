#include "Node.h"

Node::Node(long index, long x, long y):m_index(index),m_x(x),m_y(y)
{
}

long Node::Getindex() const
{
	return m_index;
}

long Node::GetX() const
{
	return m_x;
}

long Node::GetY() const
{
	return  m_y;
}

void Node::SetX(long xCoord)
{
	m_x = xCoord;

}

void Node::SetY(long yCoord)
{
	m_y = yCoord;
}
