using System;
using System.Diagnostics;
using System.Linq;

namespace ConsoleApplication1
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            Hashing hashing = new Hashing(11);
            Stopwatch stopwatch = new Stopwatch();
            
            /*hashing.Add("22");
            hashing.Add("G");
            hashing.Add("A");
            hashing.Add("B");
            hashing.Add("C");
            hashing.Add("1");
            hashing.Add("3");
            hashing.Add("8");
            //hashing.find("A");
            hashing.Display();*/
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
            
            stopwatch.Start();
            hashing.find(yes);
            stopwatch.Stop();
            Console.WriteLine("Elapsed Time is {0} ms", stopwatch.ElapsedMilliseconds);
            
        }
    }

    class Hashing
    {
        public static int increment = 0;
        
        private Node[] hashArray;
        private int lenghtArray;
        private int size;

        public int LenghtArray => lenghtArray;

        public Hashing(int capacity)
        {
            lenghtArray = capacity;
            hashArray = new Node[lenghtArray];
            size = 0;
        }
        
        
        internal class Node
        {
            private String valueOfItem;
            public string ValueOfItem
            {
                get => valueOfItem;
                set => valueOfItem = value;
            }

            private int key;
            public int Key
            {
                get => key;
                set => key = value;
            }

            public Node(String valueOfItem)
            {
                this.valueOfItem = valueOfItem;
            }
        }



        public void Add(String value)
        {
            Node node = new Node(value);
            int nodeKey;
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
            nodeKey = tmp;
            
            insert(node);
        }


        
        public void insert(Node node)
        {
            int index = HashFunc(node, hashArray);
            
            for (int i = 0; i <= hashArray.Length; i++)
            {
                if (index+i >= hashArray.Length)
                {
                    Resize(hashArray.Length);
                }
                else
                {
                    if (hashArray[index+i] == null)
                    {
                        hashArray[index+i] = node;
                        size++; 
                        break;
                    }
                }
            }
            
            if (size > hashArray.Length/2)  
            {
                Resize(hashArray.Length);
                Console.WriteLine("ZVACSUJEME");
            }
        }
        

        public int HashFunc(Node node, Node[] arr)
        {
            return node.Key % arr.Length;
        }

        public void  Resize(int capacity)
        {
            int newCapacity = capacity * capacity;
            Node[] arr = new Node[newCapacity];

            foreach (var newNode in hashArray)
            {
                if (newNode != null)
                {
                    int index = HashFunc(newNode, arr);
                    for (int i = 0; i < arr.Length; i++)
                    {
                        if (index + i >= newCapacity)
                        {
                            Resize(newCapacity);
                            break;
                        }
                        else
                        {
                            if (arr[index+i] == null)
                            {
                                arr[index + i] = newNode;
                                break;
                            }
                        }
                    }
                }
            }

            hashArray = arr;
            lenghtArray = newCapacity;
        }

        public int hashFuncFind(int key, Node[] arr)
        {
            return key % arr.Length;
        }


        public void find(string value)
        {
            int indexFind;
            int keyFind = 0;
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
            indexFind = hashFuncFind(keyFind, hashArray);
            for (int i = 0; i < hashArray.Length; i++)
            {
                if (hashArray[indexFind+i].ValueOfItem == value)
                {
                    Console.WriteLine("Najdeni prvok");
                    Console.WriteLine("{0}", hashArray[indexFind+i].ValueOfItem);
                    break;
                }
            }
        }

        public void Delete(string value)
        {
            int indexDelete;
            int keyDelete = 0;
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
            indexDelete = hashFuncFind(keyDelete, hashArray);
            for (int i = 0; i < hashArray.Length; i++)
            {
                if (hashArray[indexDelete+i].ValueOfItem.Equals(value))
                {
                    Console.WriteLine("Vymazani prvok");
                    hashArray[indexDelete + i] = null;
                    break;
                }
            }
        }
        
        public void Display()
        {
            int incrementDis = 0;
            foreach (var node in hashArray)
            {
                if (node == null)
                {
                    Console.WriteLine("riadok: {0}  NULL", incrementDis);
                }
                else
                {
                    Console.WriteLine("riadok: {0}  Key: {1}  Value: {2}",incrementDis, node.Key, node.ValueOfItem);
                }

                incrementDis++;
            }
        }
        
    }
}