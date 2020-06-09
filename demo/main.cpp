#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin9(D9), pin8(D8);
Serial xbee(D12, D11);
BBCar car(pin8, pin9, servo_ticker);

int main()
{
    char buf[256], outbuf[256];
    double pwm_table0[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table0[] = {-16.428, -16.189, -15.072, -11.723, -5.263, 0.000, 6.699, 12.201, 15.152, 16.189, 16.508};
    double pwm_table1[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table1[] = {-15.790, -15.392, -14.594, -12.122, -6.220, 0.000, 5.822, 11.643, 14.594, 15.790, 16.189};

    // first and fourth argument: length of table
    car.setCalibTable(11, pwm_table0, speed_table0, 11, pwm_table1, speed_table1);

    while (1) {
        for (int i = 0; ; i++) {
            buf[i] = xbee.getc();
            if (buf[i] == '\n') break;
        }
        RPC::call(buf, outbuf);
        xbee.printf("%s\r\n", outbuf);
    }
}