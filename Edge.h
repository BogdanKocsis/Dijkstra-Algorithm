#pragma once
class Edge
{
public:
	Edge(long source, long destionation, long weight);
	~Edge() = default;
	long GetWeight() const;
	long GetSource() const;
	long GetDestination() const;




private:
	long m_destination, m_source, m_weight;
};

