#include "Edge.h"

Edge::Edge(long source, long destionation, long weight):m_source(source),m_destination(destionation),m_weight(weight)
{
}

long Edge::GetWeight() const
{
	return m_weight;
}

long Edge::GetSource() const
{
	return m_source;
}

long Edge::GetDestination() const
{
	return m_destination;
}
