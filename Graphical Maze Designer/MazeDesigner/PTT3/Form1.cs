using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PTT3
{
    public partial class Form1 : Form
    {
        Maze CurrentMaze;

        public Form1()
        {
            InitializeComponent();
            dataGridViewMaze.RowCount = 10;

            CurrentMaze = new Maze();
            CurrentMaze.maze = new char[10, 10];

            saveFileDialog1.DefaultExt = "json";
            saveFileDialog1.FileName = "maze";
        }

        private void dataGridViewMaze_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            if (CurrentMaze.maze[e.RowIndex, e.ColumnIndex] == '#')
            {
                e.CellStyle.BackColor = Color.Black;
            } else if (CurrentMaze.maze[e.RowIndex, e.ColumnIndex] == '$')
            {
                e.CellStyle.BackColor = Color.DarkKhaki;
            }
        }

        private void dataGridViewMaze_CellClick(object sender, DataGridViewCellEventArgs e)
        {
        
        }

        private void buttonLoad_Click(object sender, EventArgs e)
        {
            DialogResult result = openFileDialog1.ShowDialog();
            if (result == DialogResult.OK)
            {
                String path = openFileDialog1.FileName;

                using (StreamReader r = new StreamReader(path))
                {
                    string json = r.ReadToEnd();

                    char[,] deserialized = JsonConvert.DeserializeObject<Maze>(json).maze;

                    CurrentMaze.maze = deserialized;

                    // This line makes sure the cell is updated.
                    dataGridViewMaze.CurrentCell = null;

                    dataGridViewMaze.Refresh();
                }

            }
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            DialogResult result = saveFileDialog1.ShowDialog();

            if(result == DialogResult.OK)
            {
                String path = saveFileDialog1.FileName;

                using (StreamWriter wr = new StreamWriter(path))
                {
                    string json = JsonConvert.SerializeObject(CurrentMaze);

                    wr.Write(json);
                }
            }
        }

        private void dataGridViewMaze_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            int row = e.RowIndex;
            int column = e.ColumnIndex;

            if (e.Button == MouseButtons.Left)
            {
                if (CurrentMaze.maze[row, column] == ' ' || CurrentMaze.maze[row,column] == '\0')
                {
                    CurrentMaze.maze[row, column] = '#';
                }
                else
                {
                    CurrentMaze.maze[row, column] = ' ';
                }
            } else
            {
                CurrentMaze.maze[row, column] = '$';
            }

            // This line makes sure the cell is updated.
            dataGridViewMaze.CurrentCell = null;
        }
    }
}
