#include <iostream>
#include <sstream>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

static int done = 0;
using namespace std;
namespace con {
	int comax() {
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);
		return (w.ws_col);
	}
	int romax() {
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);
		return (w.ws_row);
	}

	ostream& ED(ostream& s) {
		return s << string("\033[2J");
	}

	ostream& EL(ostream& s) {
		return s << string("\033[K");
	}

	class estream {
		private:
			string escape;
		public:
			estream(string e)  : escape(e) {};
			friend ostream& operator<<(ostream&, estream);
	};

	ostream& operator<<(ostream& s, estream e) {
		s << e.escape << flush;
		return s;
	}

	estream CUP(int y, int x) {
		ostringstream  sout;
		sout << "\033[" << y << ";" << x << "H";
		return estream(sout.str());
	}
	estream SGR(int r) {
		ostringstream sout;
		sout << "\033[" << r << "m";
		return estream(sout.str());
	}
}

using con::SGR;
using con::CUP;

void interruptor(int signo) {
	done = signo;
	return;
}
int kbin() // реализация обработки ввода Enter
{
	char buf[512];
	int n = 0;
	int flags = fcntl(0, F_GETFL);
	usleep(1);
	fcntl(0, F_SETFL, flags | O_NONBLOCK);
	n = read(0, buf, 512);
//	fcntl(0, F_SETFL, flags & ~O_NONBLOCK);
	return n;
}

int main(int argc, char** argv) {

	int border_x = con::comax();
	int border_y = con::romax();

	cout << con::CUP(border_y, border_x);
	cout << con::ED << flush;

	int x = border_x, y = border_y;
	int ey = border_y-1, ex = border_x-1;
	int colour = 47;

	signal(SIGINT, interruptor);
	
	int border = border_y;
	while(done < 1) {
		if(colour < 40) colour = 47;
		if(border_y >= 0) {
            cout << SGR(colour) << CUP(y, x);
            y--;
            x++;
            cout << ' ' << flush;
            usleep(2000);

            if (y == ey) {
                y = border_y;
                x = ex;
                colour--;
                if (colour < 40) colour = 47;
                ey--;
                ex--;
                if (ey < 0) ey = 0;
                if (ex <= 0) {
                    ex = 0;
                    border_y--;
                }
            }
        }
		if(kbin() > 0)
			break;

	}
	cout << CUP(1, 1) << SGR(0) << con::ED << con::EL;
	return 0;
}
