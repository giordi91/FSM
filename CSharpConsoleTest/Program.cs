using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FSMWrapper;

namespace CSharpConsoleTest
{
    class Program
    {
        static void Main(string[] args)
        {
            FSMWrapper.StateWrapper state = new FSMWrapper.StateWrapper();
            System.Console.WriteLine( state.getInt());
            System.Console.WriteLine( state.get_name());

        }
    }
}
