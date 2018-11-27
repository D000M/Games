/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package nakovAlgorithms.Mathmatics;

/**
 *
 * @author default
 */
public class Primes {
    
    private static boolean isPrime(int n) {
        for(int i = 2; i <= Math.sqrt(n); i++) {
            if(n % i == 0) {
                return false;
            }
        }
        return true;
    }
    
    public static void testPrime(int n) {
        System.out.println(isPrime(n));
    }
    
    /**
     * Glodbah Theorems
     * 1 - Всяка цяло четно число > 2, може да се представи като сума на 2 прости числа
     * n - The number we have to check
     * 10 = 3 + 7
     */
    public static void glodbahFirst(int n) {
        if( n < 2 && n % 2 != 0) {
            return;
        }

        for(int i = 1; i < n; i++) {
            int first = 0;
            int second = 0;
            if(isPrime(i)) {
                first = i;
            }
            for(int j = 1; j < n; j++) {
                if(isPrime(j)) {
                    second = j;
                    if((first + second) == n) {
                        System.out.println(first + " + " + second + " = " + n);
                    }
                }
            }  
        }
    }
    
    /**
     * 2 - Всяко цяло число > 17, може да се представи като сума на 3 прости числа.
     * @param n Числото
     */
    public static void glodbahSecond(int n) {
        
        if(n < 17) {
            return;
        }
        for(int i = 1; i < n; i++) {
            for(int j = 1; j < n; j++) {
                for(int k = 1; k < n; k++) {
                    if(isPrime(i)) {
                        if(isPrime(j)) {
                            if(isPrime(k)) {
                                if(i + j + k == n) {
                                    System.out.println(i + " + " + j + " + " + k + " " + " = " + n);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    private static boolean isPrimeInRange(int n) {
        int number = n * n;
        int range = (number + 1) * (number + 1);
        for(int i = number; i < range; i++) {
            if(isPrime(i)) {
                return true;
            }
        }
        return false;
    }
    
    public static void operamanTheorem(int n) {
        System.out.println("Is Prime in range: " + isPrimeInRange(n));
    }
    
    public static void erathostenSieve(int n) {
        boolean sieve[] = new boolean[n];
        
        for(int i = 0; i < n; i++) {
            sieve[i] = false;
        }
        int current = 2;
        while(current < n) {
            if(sieve[current] == false) {
                System.out.println(current);
                int remove = current * current;
                while(remove < n) {
                    sieve[remove] = true;
                    remove += current;
                }
            }
            current++;
        }
    } 
    
    public static void iterativePrime(int n) {
        for(int i = 2; i < n; i++) {
            if(isPrime(i)) {
                System.out.println(i);
            }
        }
    }
    
    public static void simpleDelitels(int n) {
        int how, i, j;
        System.out.println("n = " +  n);
        
        int divisors = 1;
        while(n != 1) {
            divisors++;
            how = 0;
//            System.out.print(divisors + " ");
            while(n % divisors == 0) {
                how++;
//                System.out.println(how);
                n = n / divisors;
            }
            for(j = 0; j < how; j++) {
                System.out.print(divisors + " ");
            }
        }
        System.out.println();
    }
    
    public static void mersinNumbers(int n) {
        int mersin = 1;
        for(int i = 2; i < n; i++) {
            if(isPrime(i)) {
                mersin = (int)(Math.pow(2, i)) - 1;
                if(isPrime(mersin)) {
                    System.out.println(mersin);
                }
            }
        }
    }
    
    public static long lucasLemer(int n, int count) {
        if(count > 3) {
            return n;
        }
        return lucasLemer(n * n - 2, count + 1);
    }
    
    public static void checkMersin() {
        int lucasLemer[] = new int[4];
        lucasLemer[0] = 4; 
        lucasLemer[1] = 14;
        lucasLemer[2] = 194;
        lucasLemer[3] = 37634;
        
    }
}
