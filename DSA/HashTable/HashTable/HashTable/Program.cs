using System;
using System.Collections;

namespace HashTable
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            Hashtable hashtable = new Hashtable();
            hashtable.Add(2,"anton");
            hashtable.Add(5,"maria");
            hashtable.Add(8,"perry");
            hashtable.Add(9,"choo");
            DictionaryEntry element;
            ICollection key = hashtable.Keys;
            
            Console.WriteLine(hashtable[2]);

        }
    }
}