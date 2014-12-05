#include "mtdata.h"

void MultiTouch::InitSystem()
{
	m_nTouchPointCount = 0;
	m_pTrackPath = NULL;
}

void MultiTouch::FreeSystem()
{
	while (m_pTrackPath) {
		LPTRACKPATH pTrackPath = m_pTrackPath;
		m_pTrackPath = m_pTrackPath->next;
		free(pTrackPath);
		pTrackPath = NULL;
	}
}

void MultiTouch::RecordStar(int id, int x, int y)
{
	if (m_pTrackPath == NULL) {
		m_pTrackPath = (LPTRACKPATH)malloc(sizeof(TRACKPATH));

		if (!m_pTrackPath) {
			return;
		}

		memset(m_pTrackPath, 0, sizeof(TRACKPATH));
		m_pTrackPath->next = NULL;
		m_pTrackPath->track_id = id;
		m_pTrackPath->point_count = 1;
		m_pTrackPath->current_postion = 0;
		m_pTrackPath->path[0].x = x;
		m_pTrackPath->path[0].y = y;
		m_nTouchPointCount++;
	} else {
		LPTRACKPATH pTrackPath = (LPTRACKPATH)malloc(sizeof(TRACKPATH));

		if (!pTrackPath) {
			return;
		}

		memset(pTrackPath, 0, sizeof(TRACKPATH));
		pTrackPath->next = NULL;
		pTrackPath->track_id = id;
		pTrackPath->point_count = 1;
		pTrackPath->current_postion = 0;
		pTrackPath->path[0].x = x;
		pTrackPath->path[0].y = y;		

		pTrackPath->next = m_pTrackPath;
		m_pTrackPath = pTrackPath;
		m_nTouchPointCount++;
	}
}

void MultiTouch::RecordData(int id, int x, int y)
{
	LPTRACKPATH pTrackPath = m_pTrackPath;

	while (pTrackPath) {
		if (pTrackPath->track_id == id) {
			int pid = pTrackPath->current_postion;
			int x0 = pTrackPath->path[pid].x;
			int y0 = pTrackPath->path[pid].y;

			if (((x-x0)*(x-x0)+(y-y0)*(y-y0)) < MAX_OFFSET*MAX_OFFSET) {
				pTrackPath->path[pid].x = x;
				pTrackPath->path[pid].y = y;
				break;
			}

			pTrackPath->current_postion = (pid+1)%MAX_TRACK_POINTS;
			pTrackPath->path[pTrackPath->current_postion].x = x;
			pTrackPath->path[pTrackPath->current_postion].y = y;

			if (pTrackPath->point_count+1 > MAX_TRACK_POINTS)
				pTrackPath->point_count = MAX_TRACK_POINTS;
			else
				pTrackPath->point_count = pid+1;

			break;
		}

		pTrackPath = pTrackPath->next;
	}
}

void MultiTouch::RecordFree(int id)
{
	LPTRACKPATH pTrackPath = m_pTrackPath;
	LPTRACKPATH pPreTrackPath = NULL;

	if (!m_pTrackPath) {
		return;
	}

	while (pTrackPath->track_id != id && pTrackPath->next) {
		pPreTrackPath = pTrackPath;
		pTrackPath = pTrackPath->next;
	}

	if (pTrackPath->track_id == id) {
		if (pTrackPath == m_pTrackPath) {
			m_pTrackPath = m_pTrackPath->next;
		} else {
			pPreTrackPath->next = pTrackPath->next;
		}

		free(pTrackPath);
		pTrackPath = NULL;
	}

	/*while (pTrackPath) {
		if (pTrackPath->next) {
			if (pTrackPath->next->track_id == id) {
				free(pTrackPath->next);
				pTrackPath->next = pTrackPath->next->next;
				break;
			}
		}

		if (pTrackPath->track_id == id) {

		}

		pTrackPath = pTrackPath->next;
	}*/
}

void MultiTouch::SmoothTrackPath()
{

}

void MultiTouch::PrepareGLData()
{

}