using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PTT3
{
    public partial class Form1 : Form
    {
        int[,] maze;
        public Form1()
        {
            InitializeComponent();
            dataGridView1.RowCount = 10;
            maze = new int[10, 10];

            maze[1, 2] = 1;
            maze[8, 3] = 1;
        }

        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            int row = -1;
            int column = -1;

            row = dataGridView1.CurrentCell.RowIndex;
            column = dataGridView1.CurrentCell.ColumnIndex;

            maze[row, column] = 1;

            System.Diagnostics.Debug.WriteLine((column + "," + row + " selected."));
            //dataGridView1.Refresh();

            dataGridView1.CurrentCell.Style.BackColor = Color.Black;
            dataGridView1.CurrentCell = null;
        }


        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult result = openFileDialog1.ShowDialog();
            if (result == DialogResult.OK)
            {
                String path = openFileDialog1.FileName;


            }
        }
    }
}
