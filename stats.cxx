 
#include <iostream>
#include "stats.h"
#include <cassert>
using namespace std;


namespace main_savitch_2C {

    statistician::statistician() {
        count = 0;
        total = 0;
    }

    void statistician::next(double r) {
        if (count == 0) {
            tinyest = r;
            largest = r;
        } else {
            if (r < tinyest) {
                tinyest = r;
            }
            if (r > largest) {
                largest = r;
            }
        }

        count++;
        total += r;
    }

    void statistician::reset(){
        count = 0;
        total = 0;
    }

    double statistician::mean() const {
        if (count == 0) {
            return 0.0; // Handle division by zero
        }
        return (total / count);
    }

    int statistician::length() const {
        return count;
    }

    double statistician::minimum() const {
        if (count == 0) {
            return 0.0; // Handle empty sequence
        }
        return tinyest;
    }

    double statistician::maximum() const {
        if (count == 0) {
            return 0.0; // Handle empty sequence
        }
        return largest;
    }

    double statistician::sum() const {
        return total;
    }

    // Overloaded + operator
    statistician operator +(const statistician& s1, const statistician& s2)  {
        if (s1.length( ) == 0)
        return s2;
        if (s2.length( ) == 0)
        return s1;
        statistician s3;
        s3.count = s1.count + s2.count;
        s3.total = s1.total + s2.total;
        if (s1.tinyest <= s2.tinyest){
            s3.tinyest = s1.tinyest;}
        else{
            s3.tinyest = s2.tinyest;}
        if (s1.largest >= s2.largest){
            s3.largest = s1.largest;}
        else{
            s3.largest = s2.largest;}
        return s3;
    }

    // Overloaded * operator
    statistician operator *(double scale, const statistician& s) {
        statistician s3;
        s3.total = scale * s.total;
        s3.count = s.count;
        s3.tinyest = s.tinyest * scale;
        s3.largest = s.largest * scale;
        
        if (scale > 0){
            s3.tinyest = s.tinyest * scale;
            s3.largest = s.largest * scale;
        }
        if (scale < 0){
            s3.tinyest = s.largest * scale;
            s3.largest = s.tinyest * scale;
        }
        
        return s3;
    }

    bool operator==(const statistician& s1, const statistician& s2){
        return (s1.length() == s2.length()) && (s1.sum() == s2.sum());
        assert(s1.length() > 0);
        assert(s2.length() > 0);
        (s1.minimum() == s2.minimum()) && (s1.maximum() == s2.maximum());

    }
}