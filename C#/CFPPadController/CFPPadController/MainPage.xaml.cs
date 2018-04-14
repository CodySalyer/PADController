using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Devices.Enumeration;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;
using CFPPadController;
using Windows.UI.Xaml.Media.Animation;


// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace CFPPadController
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        SerialData obj = new SerialData("UNO");

        public MainPage()
        {
            this.InitializeComponent();
            obj.SendData("Initialized");
        }

        MotorArduino frontMotor = new MotorArduino();
        MotorArduino rearMotor = new MotorArduino();


        /// <summary>
        /// These are the buttons related to the front motor trim posistion
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FrontMotorRaise_Click(object sender, RoutedEventArgs e)
        {
            
        }
        private void FrontMotorLower_Click(object sender, RoutedEventArgs e)
        {
            
        }
        private void FrontMotorTrailer_Click(object sender, RoutedEventArgs e)
        {

        }
        private void FrontMotorCruise_Click(object sender, RoutedEventArgs e)
        {

        }


        /// <summary>
        /// These are the events related to the Rear motor trim position
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        /// 
        
        private void RearMotorRaise_Click(object sender, RoutedEventArgs e)
        {
            rearMotor.AdjustTrim(-5);
            obj.SendData("RTrim "+Convert.ToString(rearMotor.TrimAngle));
            AnimateRearMotor(rearMotor.TrimAngle-90);
            TextBox.Text = "raise";
        }
        private void RearMotorLower_Click(object sender, RoutedEventArgs e)
        {
            rearMotor.AdjustTrim(5);
            obj.SendData("RTrim " + Convert.ToString(rearMotor.TrimAngle));
            AnimateRearMotor(rearMotor.TrimAngle-90);
            TextBox.Text = "lower";
        }
        private void RearMotorTrailer_Click(object sender, RoutedEventArgs e)
        {
            rearMotor.TrimAngle = 10;
            obj.SendData("RTrim " + Convert.ToString(rearMotor.TrimAngle));
            AnimateRearMotor(rearMotor.TrimAngle-90);
            TextBox.Text = "all up";
        }
        private void RearMotorCruise_Click(object sender, RoutedEventArgs e)
        {
            rearMotor.TrimAngle = 90;
            obj.SendData("RTrim " + Convert.ToString(rearMotor.TrimAngle));
            AnimateRearMotor(rearMotor.TrimAngle-90);
            TextBox.Text = "all down";
        }

        private void AnimateRearMotor(double to, double miliseconds = 100)
        {
            var storyboard = new Storyboard();
            var doubleAnimation = new DoubleAnimation();
            doubleAnimation.Duration = TimeSpan.FromMilliseconds(miliseconds);
            doubleAnimation.EnableDependentAnimation = true;
            doubleAnimation.To = to;
            Storyboard.SetTargetProperty(doubleAnimation, "Angle");
            Storyboard.SetTarget(doubleAnimation, RearMotorTransform);
            storyboard.Children.Add(doubleAnimation);
            storyboard.Begin();
        }

        private void AnimateFrontMotor(double to, double miliseconds = 100)
        {
            var storyboard = new Storyboard();
            var doubleAnimation = new DoubleAnimation();
            doubleAnimation.Duration = TimeSpan.FromMilliseconds(miliseconds);
            doubleAnimation.EnableDependentAnimation = true;
            doubleAnimation.To = to;
            Storyboard.SetTargetProperty(doubleAnimation, "Angle");
            Storyboard.SetTarget(doubleAnimation, FrontMotorTransform);
            storyboard.Children.Add(doubleAnimation);
            storyboard.Begin();
        }

    }
}
