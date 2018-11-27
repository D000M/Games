/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package courseraAlgs;

/**
 * To Slow for Huge Problems
 * @author default
 */
public class QuickFindUF {
    
    private int[] id; 
    int count;

    /**
     * Set id of each object to itself
     * @param size 
     */
    public QuickFindUF(int size) {
        count = size;
        id = new int[size];
        for(int i = 0; i < size; i++) {
            id[i] = i;
        }
    }
    
    /**
     * Check whether p and q are in the same component
     * @param p
     * @param q
     * @return 
     */
    public boolean connected(int p, int q) {
        validate(p);
        validate(q);
        return id[p] == id[q];
    }
    
    public void union(int p, int q) {
        validate(p);
        validate(q);
        
        int pId = id[p];
        int qId = id[q];
        
        for(int i = 0; i < id.length; i++) {
            if(id[i] == pId) {
                id[i] = qId;
            }
        }
        count--;
    }
    
    public int count() {
        return count;
    }
    
    public int find(int p) {
        validate(p);
        return id[p];
    }
    
    private void validate(int p) {
        int n = id.length;
        if(p < 0 || p >= n) {
            throw new IllegalArgumentException("Index: " + p + " is not in the range 0 and " + (n - 1));
        }
    }
}
