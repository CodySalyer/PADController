using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;
using Windows.Devices.SerialCommunication;
using Windows.Storage.Streams;

namespace CFPPadController
{
    class SerialData
    {
        public DeviceInformationCollection devices;
        public DeviceInformation deviceInfo;
        public SerialDevice serialDevice;
        public DataWriter dataWriter;

        public SerialData(string model)
        {
            GetDevice(model);
        }

        public async void GetDevice(string model)
        {
            if (devices == null)
            {
                if (model == "MEGA")
                {
                    string selector = SerialDevice.GetDeviceSelectorFromUsbVidPid(ArduinoDevice.MegaVid, ArduinoDevice.MegaPid);
                    this.devices = await DeviceInformation.FindAllAsync(selector);
                }
                if (model == "UNO")
                {
                    string selector = SerialDevice.GetDeviceSelectorFromUsbVidPid(ArduinoDevice.UnoVid, ArduinoDevice.UnoPid);
                    this.devices = await DeviceInformation.FindAllAsync(selector);
                }
            }
            if (devices.Count>0)
            {
                try
                {
                    this.deviceInfo = devices[0];
                    this.serialDevice = await SerialDevice.FromIdAsync(deviceInfo.Id);
                    this.serialDevice.BaudRate = 9600;
                    this.serialDevice.Parity = SerialParity.None;
                    this.serialDevice.StopBits = SerialStopBitCount.One;
                    this.serialDevice.Handshake = SerialHandshake.None;
                    this.serialDevice.DataBits = 8;
                }
                finally
                {

                }
            }
        }

        public async void SendData(string data)
        {
            if (dataWriter == null)
            {
                if (serialDevice == null) { }
                else
                {
                    dataWriter = new DataWriter(this.serialDevice.OutputStream);
                    dataWriter.WriteString(data);
                    await dataWriter.StoreAsync();
                    dataWriter.DetachStream();
                    dataWriter = null;
                }
            }
        }

        public class DeviceProperties
        {
            public const String DeviceInstanceId = "System.Devices.DeviceInstanceId";
        }

        public class ArduinoDevice
        {
            // Arduino Uno
            /// <summary>
            /// Vid is 9025 for all devices
            /// PID for the uno is 67
            /// PID for the mega is 66
            /// the values below are converted to hex
            /// </summary>
            public const UInt16 UnoVid = 0x2341;
            public const UInt16 UnoPid = 0x0043;

            // Arduino Mega
            public const UInt16 MegaVid = 0x2341;
            public const UInt16 MegaPid = 0x0042;
        }


    }

}
