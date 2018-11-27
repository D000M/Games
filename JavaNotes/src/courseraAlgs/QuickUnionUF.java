/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package courseraAlgs;

/**
 *
 * @author default
 */
public class QuickUnionUF {
    
    private int[] id;
    private int count;
    
    public QuickUnionUF(int n) {
        count = n;
        this.id = new int[n];
        
        for(int i = 0; i < n; i++) {
            id[i] = i;
        }
    }
    
    /**
     * Choose parent until reech root
     * @param i
     * @return 
     */
    private int root(int i) {
        validate(i);
        while(i != id[i]) {
            i = id[i];
        }
        return i;
    }
    
    /**
     * Check if p and q have the same root
     * @param p
     * @param q
     * @return 
     */
    public boolean connected(int p, int q) {
        return root(p) == root(q);
    }
           
    /**
     * Change root of p to point to root of q
     * @param p
     * @param q 
     */
    public void union(int p, int q) {
        int i = root(p);
        int j = root(q);
        
        if( i == j) {
            return;
        }
        
        id[i] = j;
        count--;
    }
    
    public int count() {
        return count;
    }
    
    private void validate(int p) {
        int n = id.length;
        if(n < 0 || n >= n) {
            throw new IllegalArgumentException("Index: " + p + " is not in the range 0 and " + (n - 1));
        }
    }
}
