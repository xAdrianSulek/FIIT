using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

namespace HashTable
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            Hashing hashing = new Hashing(11);
            Stopwatch stopwatch = new Stopwatch();
            
            ///dobre hodnoty pre ukazku fukncii
            hashing.Add("G"); //<--- index 5
            hashing.Add("22"); //<--- tiez index 5
            hashing.Add("A");
            hashing.Add("B");
            hashing.Add("C");
            hashing.Find("22");
            //hashing.Delete("22");
            hashing.Display();
            
            var chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
            var stringChars = new char[4];
            var random = new Random();
            
            string yes = null;
            for (int i = 0; i < 900000; i++)
            {
                for (int j = 0; j < stringChars.Length; j++)
                {
                    stringChars[j] = chars[random.Next(chars.Length)];
                }

                var finalString = new String(stringChars);
                yes = finalString;
                hashing.Add(finalString);
            }
        }
    }

    class Hashing
    {
        private Node[] hashArray;
        private int lengthOfArray;
        private int size;

        public Hashing(int capacity)
        {
            lengthOfArray = capacity;
            hashArray = new Node[lengthOfArray];
            size = 0;
        }
        
        
        
        
        internal class Node
        {
            private int key;
            private string value;
            private LinkedList<Node> nodeLinkedList = new LinkedList<Node>();

            public string Value => value;

            public LinkedList<Node> NodeLinkedList
            {
                get => nodeLinkedList;
                set => nodeLinkedList = value;
            }

            public int Key
            {
                get => key;
                set => key = value;
            }

            public Node(string value)
            {
                this.value = value;
            }
        }

        public void Add(string value)
        {
            Node node = new Node(value);
            int tmp = 0;
            foreach (var s in value)
            {
                /// Generacia unikatneho kluca zo stringu
                if ((s >= 'a' && s <= 'z')  ||  (s >= '0' && s <= '9')  ||  (s >= 'A' &&  s <= 'Z'))
                {
                    tmp = tmp * 31 + s;
                }
            }
            node.Key = tmp;
            node.NodeLinkedList.AddLast(node);
            Insert(node);
        }

        public int HashFunc(Node node, Node[] arr)
        {
            return node.Key % arr.Length;
        }

        public int hashFuncInt(int key, Node[] arr)
        {
            return key % arr.Length;
        }

        public void Insert(Node node)
        {
            int index = HashFunc(node, hashArray);
            if (hashArray[index] == null)
            {
                hashArray[index] = node;
                size++;
            }
            else
            {
                hashArray[index].NodeLinkedList.AddLast(node);
                size++;
            }


            if (size > hashArray.Length/2)
            {
                Console.WriteLine("Resizujeme");
                Resize(hashArray.Length);
            }
        }

        public void Resize(int Capacity)
        {
            int newCapacity = hashArray.Length * hashArray.Length;
            Node[] newArr = new Node[newCapacity];

            foreach (var newNode in hashArray)
            {
                if (newNode != null)
                {
                    foreach (var newNodeLinked in newNode.NodeLinkedList)
                    {
                        int index = HashFunc(newNodeLinked, newArr);
                        if (newArr[index] == null)
                        {
                            newArr[index] = newNodeLinked;
                        }
                        else
                        {
                            newArr[index].NodeLinkedList.AddLast(newNodeLinked);
                        }
                    }
                }

                hashArray = newArr;
                lengthOfArray = newCapacity;
            }
        }


        public void Find(string value)
        {
            int indexFind;
            int keyFind;
            int tmp = 0;
            foreach (var s in value)
            {
                /// Generacia unikatneho kluca zo stringu
                if ((s >= 'a' && s <= 'z')  ||  (s >= '0' && s <= '9')  ||  (s >= 'A' &&  s <= 'Z'))
                {
                    tmp = tmp * 31 + s;
                }
            }

            keyFind = tmp;
            indexFind = hashFuncInt(keyFind, hashArray);
            

            if (hashArray[indexFind].Value.Equals(value))
            {
                Console.WriteLine("Najdeni prvok {0}", value);
            }
            else
            {
                bool found = false;
                foreach (var node in hashArray[indexFind].NodeLinkedList)
                {
                    if (node.Value.Equals(value))
                    {
                        Console.WriteLine("Najdeni prvok {0}", value);
                        found = true;
                        break;
                    }
                }
                if (found == false)
                {
                    Console.WriteLine("Prvok nebol najdeny");
                }
            }
        }


        public void Delete(string value)
        {
            int indexDelete;
            int keyDelete;
            int tmp = 0;
            foreach (var s in value)
            {
                /// Generacia unikatneho kluca zo stringu
                if ((s >= 'a' && s <= 'z')  ||  (s >= '0' && s <= '9')  ||  (s >= 'A' &&  s <= 'Z'))
                {
                    tmp = tmp * 31 + s;
                }
            }

            keyDelete = tmp;
            indexDelete = hashFuncInt(keyDelete, hashArray);

            if (hashArray[indexDelete].Value.Equals(value))
            {
                if (hashArray[indexDelete].NodeLinkedList.Count < 2)
                {
                    hashArray[indexDelete] = null;
                }
                else
                {
                    foreach (var node in hashArray[indexDelete].NodeLinkedList)
                    {
                        if (node.Value.Equals(value))
                        {
                            hashArray[indexDelete].NodeLinkedList.Remove(node);
                            break;
                        }
                    }
                }
            }
            else
            {
                foreach (var node in hashArray[indexDelete].NodeLinkedList)
                {
                    if (node.Value.Equals(value))
                    {
                        hashArray[indexDelete].NodeLinkedList.Remove(node);
                        break;
                    }
                }
            }
        }
        


        public void Display()
        {
            ///Zobrazenie hashovacej tabulky
            ///Odporucam len pre pole velkosti 11 alebo 121. inak zakomentovat/dat prec Display z mainu
            
            int incrementDis = 0;
            foreach (var node in hashArray)
            {
                if (node == null)
                {
                    Console.WriteLine("riadok: {0}  NULL", incrementDis);
                }
                
                else
                {
                    int linkedIncrement = 0;
                    foreach (var linked in node.NodeLinkedList)
                    {
                        Console.WriteLine("riadok: {0}  riadok linkedListu {1}   Value: {2}   Key:  {3}", incrementDis, linkedIncrement, linked.Value, linked.Key);
                        linkedIncrement++;
                    }
                }
                incrementDis++;
            }
            
            
        }
    }
}