static void centeredmaster(Monitor *m);
static void centeredfloatingmaster(Monitor *m);
static void fibonacci(Monitor *m, int s);
static void dwindle(Monitor *m);
static void spiral(Monitor *m);
static void deck(Monitor *m);
static void tile(Monitor *m);
static void monocle(Monitor *m);

/** centeredmaster **/
/* https://dwm.suckless.org/patches/centeredmaster/
   centeredmaster and centeredfloatingmaster are two stack layouts for dwm.
   centeredmaster centers the nmaster area on screen, using mfact * monitor width & height, with the stacked windows
   distributed to the left and right. It can be selected with [Win]+[u].
   With one and two clients in master respectively this results in:
   +------------------------------+       +------------------------------+
   |+--------++--------++--------+|       |+--------++--------++--------+|
   ||        ||        ||        ||       ||        ||        ||        ||
   ||        ||        ||        ||       ||        ||   M1   ||        ||
   ||        ||        ||        ||       ||        ||        ||        ||
   ||  S2    ||   M    ||   S1   ||       ||        |+--------+|        ||
   ||        ||        ||        ||       ||        |+--------+|        ||
   ||        ||        ||        ||       ||        ||        ||        ||
   ||        ||        ||        ||       ||        ||   M2   ||        ||
   ||        ||        ||        ||       ||        ||        ||        ||
   |+--------++--------++--------+|       |+--------++--------++--------+|
   +------------------------------+       +------------------------------+
*/
void centeredmaster(Monitor *m)
{
	unsigned int i, n, h, mw, mx, my, oty, ety, tw;
	Client *c;

	/* count number of clients in the selected monitor */
	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

	/* initialize areas */
	mw = m->ww;
	mx = 0;
	my = 0;
	tw = mw;

	if (n > m->nmaster) {
		/* go mfact box in the center if more than nmaster clients */
		mw = m->nmaster ? m->ww * m->mfact : 0;
		tw = m->ww - mw;

		if (n - m->nmaster > 1) {
			/* only one client */
			mx = (m->ww - mw) / 2;
			tw = (m->ww - mw) / 2;
		}
	}

	oty = 0;
	ety = 0;
	for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
	  	if (i < m->nmaster) {
		/* nmaster clients are stacked vertically, in the center
		 * of the screen */
		h = (m->wh - my) / (MIN(n, m->nmaster) - i);
		resize(c, m->wx + mx, m->wy + my, mw - (2*c->bw),
		       h - (2*c->bw), 0);
		my += HEIGHT(c);
	} else {
		/* stack clients are stacked vertically */
		if ((i - m->nmaster) % 2 ) {
			h = (m->wh - ety) / ( (1 + n - i) / 2);
			resize(c, m->wx, m->wy + ety, tw - (2*c->bw),
			       h - (2*c->bw), 0);
			ety += HEIGHT(c);
		} else {
			h = (m->wh - oty) / ((1 + n - i) / 2);
			resize(c, m->wx + mx + mw, m->wy + oty,
			       tw - (2*c->bw), h - (2*c->bw), 0);
			oty += HEIGHT(c);
		}
	}
}
/**
   centeredfloatingmaster centers the nmaster area on screen, using mfact * monitor width & height over a horizontally tiled
   stack area, comparable to a scratchpad. It can be selected with [Win]+[o].

   With one and two clients in master respectively this results in:
   +------------------------------+       +------------------------------+
   |+--------++--------++--------+|       |+--------++--------++--------+|
   ||        ||        ||        ||       ||        ||        ||        ||
   ||    +------------------+    ||       ||    +--------++--------+    ||
   ||    |                  |    ||       ||    |        ||        |    ||
   ||    |                  |    ||       ||    |        ||        |    ||
   ||    |        M         |    ||       ||    |   M1   ||   M2   |    ||
   ||    |                  |    ||       ||    |        ||        |    ||
   ||    +------------------+    ||       ||    +--------++--------+    ||
   ||        ||        ||        ||       ||        ||        ||        ||
   |+--------++--------++--------+|       |+--------++--------++--------+|
   +------------------------------+       +------------------------------+
   These stack layouts can be useful on large screens, where monocle or htile might be either too large or forcing the user to
   type in a corner of the screen. They allow for instance to center the editor while being able to keep an eye on background
   processes (logs, tests,...)
**/
void centeredfloatingmaster(Monitor *m)
{
	unsigned int i, n, w, mh, mw, mx, mxo, my, myo, tx;
	Client *c;

	/* count number of clients in the selected monitor */
	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

	/* initialize nmaster area */
	if (n > m->nmaster) {
		/* go mfact box in the center if more than nmaster clients */
		if (m->ww > m->wh) {
			mw = m->nmaster ? m->ww * m->mfact : 0;
			mh = m->nmaster ? m->wh * 0.9 : 0;
		} else {
			mh = m->nmaster ? m->wh * m->mfact : 0;
			mw = m->nmaster ? m->ww * 0.9 : 0;
		}
		mx = mxo = (m->ww - mw) / 2;
		my = myo = (m->wh - mh) / 2;
	} else {
		/* go fullscreen if all clients are in the master area */
		mh = m->wh;
		mw = m->ww;
		mx = mxo = 0;
		my = myo = 0;
	}

	for(i = tx = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
	if (i < m->nmaster) {
		/* nmaster clients are stacked horizontally, in the center
		 * of the screen */
		w = (mw + mxo - mx) / (MIN(n, m->nmaster) - i);
		resize(c, m->wx + mx, m->wy + my, w - (2*c->bw),
		       mh - (2*c->bw), 0);
		mx += WIDTH(c);
	} else {
		/* stack clients are stacked horizontally */
		w = (m->ww - tx) / (n - i);
		resize(c, m->wx + tx, m->wy, w - (2*c->bw),
		       m->wh - (2*c->bw), 0);
		tx += WIDTH(c);
	}
}

/** Fibonacci **/
void fibonacci(Monitor *mon, int s)
{
	unsigned int i, n, nx, ny, nw, nh;
	Client *c;

	for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++);
	if(n == 0)
		return;
	
	nx = mon->wx;
	ny = 0;
	nw = mon->ww;
	nh = mon->wh;
	
	for(i = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
		if((i % 2 && nh / 2 > 2 * c->bw)
		   || (!(i % 2) && nw / 2 > 2 * c->bw)) {
			if(i < n - 1) {
				if(i % 2)
					nh /= 2;
				else
					nw /= 2;
				if((i % 4) == 2 && !s)
					nx += nw;
				else if((i % 4) == 3 && !s)
					ny += nh;
			}
			if((i % 4) == 0) {
				if(s)
					ny += nh;
				else
					ny -= nh;
			}
			else if((i % 4) == 1)
				nx += nw;
			else if((i % 4) == 2)
				ny += nh;
			else if((i % 4) == 3) {
				if(s)
					nx += nw;
				else
					nx -= nw;
			}
			if(i == 0)
			{
				if(n != 1)
					nw = mon->ww * mon->mfact;
				ny = mon->wy;
			}
			else if(i == 1)
				nw = mon->ww - nw;
			i++;
		}
		resize(c, nx, ny, nw - 2 * c->bw, nh - 2 * c->bw, False);
	}
}
/*
 +-----------+-----------+  +-----------+-----------+
 |           |           |  |           |           |
 |           |     2     |  |           |     2     |
 |           |           |  |           |           |
 |     1     +--+--+-----+  |     1     +-----+-----+
 |           | 5|-.|     |  |           |     |  4  |
 |           +--+--+  3  |  |           |  3  +--+--+
 |           |  4  |     |  |           |     | 5|-.|
 +-----------+-----+-----+  +-----------+-----+-----+
	  spiral                     dwindle
*/
void dwindle(Monitor *mon) {
  fibonacci(mon, 1);
}

void spiral(Monitor *mon) {
  fibonacci(mon, 0);
}

/* Deck layout */
/**
 Deck:
+-----------------+--------+
|                 |        |
|                 |        |
|                 |        |
|        M        |   S1   |
|                 |        |
|                 |        |
|                 |        |
+-----------------+--------+
**/
void deck(Monitor *m) {
  unsigned int i, n, h, mw, my;
  Client *c;

  for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
  if(n == 0)
    return;
  if(n > m->nmaster) {
    mw = m->nmaster ? m->ww * m->mfact : 0;
    snprintf(m->ltsymbol, sizeof m->ltsymbol, "[%d]", n - m->nmaster);
  } else mw = m->ww;
  for(i = my = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
    if(i < m->nmaster) {
      h = (m->wh - my) / (MIN(n, m->nmaster) - i);
      resize(c, m->wx, m->wy + my, mw - (2*c->bw), h - (2*c->bw), False);
      my += HEIGHT(c);
    } else resize(c, m->wx + mw, m->wy, m->ww - mw - (2*c->bw), m->wh - (2*c->bw), False);
}

/* Tile */
/*
  +-----------------+--------+
  |                 |        |
  |                 |  S1    |
  |                 |        |
  |        M        +--------+
  |                 |        |
  |                 |   S2   |
  |                 |        |
  +-----------------+--------+
*/
void tile(Monitor *m)
{
	unsigned int i, n, h, mw, my, ty;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

	if (n > m->nmaster)
		mw = m->nmaster ? m->ww * m->mfact : 0;
	else
		mw = m->ww;
	for (i = my = ty = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
		if (i < m->nmaster) {
			h = (m->wh - my) / (MIN(n, m->nmaster) - i);
			resize(c, m->wx, m->wy + my, mw - (2*c->bw), h - (2*c->bw), 0);
			if (my + HEIGHT(c) < m->wh)
				my += HEIGHT(c);
		} else {
			h = (m->wh - ty) / (n - i);
			resize(c, m->wx + mw, m->wy + ty, m->ww - mw - (2*c->bw), h - (2*c->bw), 0);
			if (ty + HEIGHT(c) < m->wh)
				ty += HEIGHT(c);
		}
}

// Monocle
/*
  +--------------------------+
  |                          |
  |                          |
  |                          |
  |             M            |
  |                          |
  |                          |
  |                          |
  +--------------------------+
*/

void monocle(Monitor *m)
{
	unsigned int n = 0;
	Client *c;

	for (c = m->clients; c; c = c->next)
		if (ISVISIBLE(c))
			n++;
	if (n > 0) /* override layout symbol */
		snprintf(m->ltsymbol, sizeof m->ltsymbol, "[%d]", n);
	for (c = nexttiled(m->clients); c; c = nexttiled(c->next))
		resize(c, m->wx, m->wy, m->ww - 2 * c->bw, m->wh - 2 * c->bw, 0);
}


