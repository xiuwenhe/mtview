
#define MAX_TRACK_POINTS 20;
#define MAX_OFFSET       8;

typedef struct {
	int x;
	int y;
}POINT2D, *LPPOINT2D;

typedef struct {
	LPTRACKPATH   next;
	int           track_id;
	int           point_count;
	int           current_postion;
	POINT2D       path[MAX_TRACK_POINTS];
}TRACKPATH, *LPTRACKPATH;

class MultiTouch {

private:
	int         m_nTouchPointCount;
	LPTRACKPATH m_pTrackPath;

public:
	void InitSystem();
	void FreeSystem();

	void RecordStar(int id, int x, int y);
	void RecordData(int id, int x, int y);
	void RecordFree(int id);

	void SmoothTrackPath();
	void PrepareGLData();
};