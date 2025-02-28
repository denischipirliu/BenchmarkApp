using ProgressBarSample;

namespace BenchmarkAppGUI
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        // Declare controls
        private Label CPU_name_label;
        private TextBox CPU_name_textbox;
        private Label CPU_arch_label;
        private TextBox CPU_arch_textbox;
        private Label CPU_physical_cores_label;
        private TextBox CPU_physical_cores_textbox;
        private Label CPU_logical_cores_label;
        private TextBox CPU_logical_cores_textbox;
        private Label CPU_clock_label;
        private TextBox CPU_clock_textbox;
        private Label RAM_size_label;
        private TextBox RAM_size_textbox;
        private Label RAM_load_label;
        private TextBox RAM_load_textbox;
        private Label GPU_model_label;
        private TextBox GPU_model_textbox;

        private Label data_benchmark_read_label;
        private TextBox data_benchmark_read_textbox;
        private Label data_benchmark_write_label;
        private TextBox data_benchmark_write_textbox;
        private Button data_benchmark_button;

        private Label CPU_single_core_benchmark_label;
        private TextProgressBar CPU_single_core_benchmark_textbox;
        private Label CPU_multi_core_benchmark_label;
        private TextProgressBar CPU_multi_core_benchmark_textbox;
        private Button CPU_benchmark_button;


        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        private void InitializeComponent()
        {
            // System Info GroupBox
            GroupBox systemInfoGroup = new GroupBox();
            systemInfoGroup.Text = "System Info";
            systemInfoGroup.Location = new Point(10, 10);
            systemInfoGroup.Size = new Size(500, 450);
            systemInfoGroup.ForeColor = Color.Black;
            systemInfoGroup.BackColor = Color.LightSkyBlue;

            this.CPU_name_label = new Label() { Text = "CPU Name", Location = new Point(10, 40), ForeColor = Color.Black, AutoSize = true };
            this.CPU_name_textbox = new TextBox() { Location = new Point(170, 40), Width = 300, ReadOnly = true, BackColor = Color.AliceBlue, ForeColor = Color.Black, TextAlign = HorizontalAlignment.Center };
            systemInfoGroup.Controls.Add(this.CPU_name_label);
            systemInfoGroup.Controls.Add(this.CPU_name_textbox);

            this.CPU_arch_label = new Label() { Text = "CPU Architecture", Location = new Point(10, 90), ForeColor = Color.Black, AutoSize = true };
            this.CPU_arch_textbox = new TextBox() { Location = new Point(170, 90), Width = 150, ReadOnly = true, BackColor = Color.AliceBlue, ForeColor = Color.Black, TextAlign = HorizontalAlignment.Center };
            systemInfoGroup.Controls.Add(this.CPU_arch_label);
            systemInfoGroup.Controls.Add(this.CPU_arch_textbox);

            this.CPU_physical_cores_label = new Label() { Text = "Physical Cores", Location = new Point(10, 140), ForeColor = Color.Black, AutoSize = true };
            this.CPU_physical_cores_textbox = new TextBox() { Location = new Point(170, 140), Width = 150, ReadOnly = true, BackColor = Color.AliceBlue, ForeColor = Color.Black, TextAlign = HorizontalAlignment.Center };
            systemInfoGroup.Controls.Add(this.CPU_physical_cores_label);
            systemInfoGroup.Controls.Add(this.CPU_physical_cores_textbox);

            this.CPU_logical_cores_label = new Label() { Text = "Logical Cores", Location = new Point(10, 190), ForeColor = Color.Black, AutoSize = true };
            this.CPU_logical_cores_textbox = new TextBox() { Location = new Point(170, 190), Width = 150, ReadOnly = true, BackColor = Color.AliceBlue, ForeColor = Color.Black, TextAlign = HorizontalAlignment.Center };
            systemInfoGroup.Controls.Add(this.CPU_logical_cores_label);
            systemInfoGroup.Controls.Add(this.CPU_logical_cores_textbox);

            this.CPU_clock_label = new Label() { Text = "CPU Clock", Location = new Point(10, 240), ForeColor = Color.Black, AutoSize = true };
            this.CPU_clock_textbox = new TextBox() { Location = new Point(170, 240), Width = 150, ReadOnly = true, BackColor = Color.AliceBlue, ForeColor = Color.Black, TextAlign = HorizontalAlignment.Center };
            systemInfoGroup.Controls.Add(this.CPU_clock_label);
            systemInfoGroup.Controls.Add(this.CPU_clock_textbox);

            this.RAM_size_label = new Label() { Text = "RAM Size", Location = new Point(10, 290), ForeColor = Color.Black, AutoSize = true };
            this.RAM_size_textbox = new TextBox() { Location = new Point(170, 290), Width = 150, ReadOnly = true, BackColor = Color.AliceBlue, ForeColor = Color.Black, TextAlign = HorizontalAlignment.Center };
            systemInfoGroup.Controls.Add(this.RAM_size_label);
            systemInfoGroup.Controls.Add(this.RAM_size_textbox);

            this.RAM_load_label = new Label() { Text = "RAM Load", Location = new Point(10, 340), ForeColor = Color.Black, AutoSize = true };
            this.RAM_load_textbox = new TextBox() { Location = new Point(170, 340), Width = 150, ReadOnly = true, BackColor = Color.AliceBlue, ForeColor = Color.Black, TextAlign = HorizontalAlignment.Center };
            systemInfoGroup.Controls.Add(this.RAM_load_label);
            systemInfoGroup.Controls.Add(this.RAM_load_textbox);

            this.GPU_model_label = new Label() { Text = "GPU Model", Location = new Point(10, 390), ForeColor = Color.Black, AutoSize = true };
            this.GPU_model_textbox = new TextBox() { Location = new Point(170, 390), Width = 300, ReadOnly = true, BackColor = Color.AliceBlue, ForeColor = Color.Black, TextAlign = HorizontalAlignment.Center };
            systemInfoGroup.Controls.Add(this.GPU_model_label);
            systemInfoGroup.Controls.Add(this.GPU_model_textbox);

            this.Controls.Add(systemInfoGroup);

            // Data Benchmark GroupBox
            GroupBox dataBenchmarkGroup = new GroupBox();
            dataBenchmarkGroup.Text = "Data Benchmark";
            dataBenchmarkGroup.Location = new Point(530, 10);
            dataBenchmarkGroup.Size = new Size(360, 200);
            dataBenchmarkGroup.ForeColor = Color.Black;
            dataBenchmarkGroup.BackColor = Color.LightSkyBlue;

            this.data_benchmark_read_label = new Label() { Text = "Read Speed", Location = new Point(10, 40), ForeColor = Color.Black, AutoSize = true };
            this.data_benchmark_read_textbox = new TextBox() { Location = new Point(130, 40), Width = 200, ReadOnly = true, BackColor = Color.AliceBlue, ForeColor = Color.Black, TextAlign = HorizontalAlignment.Center };
            dataBenchmarkGroup.Controls.Add(this.data_benchmark_read_label);
            dataBenchmarkGroup.Controls.Add(this.data_benchmark_read_textbox);

            this.data_benchmark_write_label = new Label() { Text = "Write Speed", Location = new Point(10, 80), ForeColor = Color.Black, AutoSize = true };
            this.data_benchmark_write_textbox = new TextBox() { Location = new Point(130, 80), Width = 200, ReadOnly = true, BackColor = Color.AliceBlue, ForeColor = Color.Black, TextAlign = HorizontalAlignment.Center };
            dataBenchmarkGroup.Controls.Add(this.data_benchmark_write_label);
            dataBenchmarkGroup.Controls.Add(this.data_benchmark_write_textbox);

            this.data_benchmark_button = new Button() { Text = "Start Benchmark", Location = new Point(110, 140), Width = 100, BackColor = Color.CornflowerBlue, ForeColor = Color.White, FlatStyle = FlatStyle.Flat, AutoSize = true };
            dataBenchmarkGroup.Controls.Add(this.data_benchmark_button);

            this.Controls.Add(dataBenchmarkGroup);

            // CPU Benchmark GroupBox
            GroupBox cpuBenchmarkGroup = new GroupBox();
            cpuBenchmarkGroup.Text = "CPU Benchmark";
            cpuBenchmarkGroup.Location = new Point(530, 260);
            cpuBenchmarkGroup.Size = new Size(360, 200);
            cpuBenchmarkGroup.ForeColor = Color.Black;
            cpuBenchmarkGroup.BackColor = Color.LightSkyBlue;

            this.CPU_single_core_benchmark_label = new Label() { Text = "Single Core", Location = new Point(10, 40), ForeColor = Color.Black, AutoSize = true };
            this.CPU_single_core_benchmark_textbox = new TextProgressBar() { Location = new Point(130, 40), Width = 200, VisualMode = ProgressBarDisplayMode.CustomText, Maximum = 10000, Height = data_benchmark_read_textbox.Height + 3, ProgressColor = Color.IndianRed };
            cpuBenchmarkGroup.Controls.Add(this.CPU_single_core_benchmark_label);
            cpuBenchmarkGroup.Controls.Add(this.CPU_single_core_benchmark_textbox);

            this.CPU_multi_core_benchmark_label = new Label() { Text = "Multi Core", Location = new Point(10, 80), ForeColor = Color.Black, AutoSize = true };
            this.CPU_multi_core_benchmark_textbox = new TextProgressBar() { Location = new Point(130, 80), Width = 200, VisualMode = ProgressBarDisplayMode.CustomText, Maximum = 10000, Height = data_benchmark_read_textbox.Height + 3, ProgressColor = Color.IndianRed };
            cpuBenchmarkGroup.Controls.Add(this.CPU_multi_core_benchmark_label);
            cpuBenchmarkGroup.Controls.Add(this.CPU_multi_core_benchmark_textbox);

            this.CPU_benchmark_button = new Button() { Text = "Start Benchmark", Location = new Point(110, 140), Width = 100, BackColor = Color.CornflowerBlue, ForeColor = Color.White, FlatStyle = FlatStyle.Flat, AutoSize = true };
            cpuBenchmarkGroup.Controls.Add(this.CPU_benchmark_button);

            this.Controls.Add(cpuBenchmarkGroup);

            // General form settings
            this.ClientSize = new Size(900, 480);
            this.BackColor = Color.LightSkyBlue;
            this.Text = "Benchmark App";
            this.ForeColor = Color.Black;
            this.Font = new Font("Segoe UI", 10);
        }

        #endregion
    }


}