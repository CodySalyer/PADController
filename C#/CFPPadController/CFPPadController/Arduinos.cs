using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;
using Windows.Devices.SerialCommunication;
using Windows.Storage.Streams;

namespace CFPPadController
{
    public class ControllerArduino
    {
        public int Direction { get; set; }
        public int Magnitude { get; set; }
        public string Mode { get; set; }
        public List<int> ErrorCodes;

        // Device info for Serial communication
        public ControllerArduino(/*Device watcher information*/)
        {

        }
    }
    public class MotorArduino
    {
        public int Direction { get; set; }
        public int Thrust { get; set; }
        private int trimAngle = 0;
        public int TrimAngle
        {
            get
            {
                return trimAngle;
            }
            set
            {
                if(value > 90)
                {
                    trimAngle = 90;
                }
                else if(value < 10)
                {
                    trimAngle = 10;
                }
                else
                {
                    trimAngle = value;
                }
            }
        }

        public string Mode { get; set; }
        public List<int> ErrorCodes;

        // Device info for Serial communication
        public MotorArduino(/*Device watcher information*/)
        {
            this.TrimAngle = 0;
        }
        public void AdjustTrim(int adjustment)
        {
            this.TrimAngle = this.TrimAngle + adjustment;
        }


    }
}
