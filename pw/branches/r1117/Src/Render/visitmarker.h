#pragma once

class VisitMarkerProvider
{
	friend class VisitMarker;

private:
	int counter;

public:
	VisitMarkerProvider() : counter(0) {}
	void Update() { ++counter; }
};

class VisitMarker
{
private:
	int mark;

public:
	VisitMarker() : mark(-1) {}

	void Mark(VisitMarkerProvider const &marker) { mark = marker.counter; }
	bool IsOutdated(VisitMarkerProvider const &marker) const { return (mark != marker.counter); }
};
