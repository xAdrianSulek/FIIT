using System;
using System.Diagnostics;

namespace BST_SplayTree
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            SplayTree splayTree = new SplayTree();
            Stopwatch stopwatch = new Stopwatch();
            Random random = new Random();
            
            
            
            /*
            splayTree.Insert(10);
            splayTree.Insert(5);
            splayTree.Insert(8);
            splayTree.Insert(2);
            splayTree.Insert(20);
            splayTree.Find(20,splayTree.root);
            splayTree.Display(splayTree.root);
            Console.WriteLine(splayTree.root.Key); //<--- Vidime ze root sa zmeni na 20 po vyhladani daneho Nodu
            */
            

            
            for (int i = 1; i < 1000000; i++)
            {
                splayTree.Insert(i);
            }
            
            for (int i = 1; i < 1000; i++)
            {
                int rnd = random.Next();
                stopwatch.Start();
                splayTree.Find(rnd/2,splayTree.root);
                stopwatch.Stop();
            }

            Console.WriteLine("Elapsed Time is {0} ms", stopwatch.ElapsedMilliseconds);
        }
    }

    class SplayTree
    {
        public Node root;

        public SplayTree()
        {
            root = null;
        }
        internal class Node
        {
            private int key;
            private Node left;
            private Node right;

            public int Key
            {
                get => key;
                set => key = value;
            }

            public Node Left
            {
                get => left;
                set => left = value;
            }

            public Node Right
            {
                get => right;
                set => right = value;
            }

            public Node(int key)
            {
                this.key = key;
                left = null;
                right = null;
            }
        }


        public void Insert(int key)
        {
            if (root == null)
            {
                root = new Node(key);
                return;
            }

            root = Splay(key, root);

            if (key < root.Key)
            {
                Node temp = new Node(key);
                temp.Left = root.Left;
                temp.Right = root;
                root.Left = null;
                root = temp;
            }
            else if (key > root.Key)
            {
                Node temp = new Node(key);
                temp.Right = root.Right;
                temp.Left = root;
                root.Right = null;
                root = temp;
            }

        }

        public Node Find(int key, Node node)
        {
            node = Splay(key, node);

            if (node.Key == key)
            {
                return node;
            }
            else
            {
                Console.WriteLine("Nenasiel sa prvok");
                return null;
            }

            //Na checkovanie Funkcnosti
            /*if (root.Key == key)
            {
                Console.WriteLine("Najdeny prvok");
            }
            else
            {
                Find(key, root.Left);
                Find(key, root.Right);
            }*/
        }

        public void Delete(int key)
        {
            if (root == null)
            {
                return;
            }

            root = Splay(key, root);

            if (root.Key != key)
            {
                return;
            }

            if (root.Left == null)
            {
                root = root.Right;
            }
            else
            {
                Node temp = root.Right;
                root = root.Left;
                Splay(key, root);
                root.Right = temp;
            }
        }

        private Node Splay(int key, Node node)
        {
            if (node == null || node.Key == key)
            {
                return node;
            }

            if (key < node.Key)
            {
                if (node.Left == null)
                    return node;

                if (key < node.Left.Key)
                {
                    node.Left.Left = Splay(key, node.Left.Left);
                    node = RotateRight(node);
                }
                else if (key > node.Left.Key)
                {
                    node.Left.Right = Splay(key, node.Left.Right);
                    if (node.Left.Right != null)
                        node.Left = RotateLeft(node.Left);
                }

                if (node.Left == null)
                    return node;
                else
                    return RotateRight(node);
            }


            else
            {
                if (node.Right == null)
                    return node;

                if (key < node.Right.Key)
                {
                    node.Right.Left = Splay(key, node.Right.Left);
                    if (node.Right.Left != null)
                        node.Right = RotateRight(node.Right);
                }
                else if (key > node.Right.Key)
                {
                    node.Right.Right = Splay(key, node.Right.Right);
                    node = RotateLeft(node);
                }

                if (node.Right == null)
                    return node;
                else
                    return RotateLeft(node);
            }
        }
        
        private Node RotateRight(Node node)
        {
            Node temp = node.Left;
            node.Left = temp.Right;
            temp.Right = node;
            return temp;
        }
        
        private Node RotateLeft(Node node)
        {
            Node temp = node.Right;
            node.Right = temp.Left;
            temp.Left = node;
            return temp;
        }



        public void Display(Node node)
        {
            if (node != null)
            {
                Display(node.Left);
                Console.WriteLine(node.Key + "  ");
                Display(node.Right);
            }
        }
    }
}