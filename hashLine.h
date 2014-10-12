#ifndef HASHLINE_H
#define HASHLINE_H

#include <map>

#include <QPoint>
#include <QHash>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

using namespace std;

struct HashPoint{
    int operator()( const QPoint& p ) const {
        return  QHash< int, int >().value( p.x() ) ^ QHash< int, int >().value( p.y() );
    }
};

int GCD( const int a, const int b ){
    int gcd = 1;
    for( int i = 2; i <= a && i <= b; i++ ){
        if( ( a%i==0 ) && ( b%i==0 ) ){
            gcd = i;
        }
    }
    return gcd;
}

int GCD2( const int a, const int b ){
    int min_ab = ( a < b ? a : b );
    for( int i = min_ab; i >= 2; i-- ){
        if( ( a%i == 0 ) && ( b%i == 0 ) ) {
            return i;
        }
    }
    return 1;
}

std::pair<int, int> get_canonical_fractional( int a, int b ){

    int gcd = GCD2( abs(a), abs(b) );
    a /= gcd;
    b /= gcd;

    return b < 0 ? make_pair( -a, -b ) : make_pair( a, b );
}

struct Line{
    Line( const QPoint& a, const QPoint& b ) :
        slope( a.x() != b.x() ? get_canonical_fractional( b.y() - a.y(), b.x() - a.x() )
                              : make_pair( 1, 0 ) ),
        intercept( a.x() != b.x() ? get_canonical_fractional( b.x() * a.y() - a.x() * b.y(), b.x() - a.x() )
                                  : make_pair( a.x(), 1 ) ) {}

    bool operator==( const Line& other ) const {
        return slope == other.slope && intercept == other.intercept;
    }

    std::pair< int, int > slope;
    std::pair< int, int > intercept;

    int y( const int x ){
        return slope.second ? int ( double( x ) * double( slope.first ) / double( slope.second ) +
                             double( intercept.first ) / double( intercept.second ) )
                     : x;
    }
};

struct HashLine {
    size_t operator()( const Line& l ) const {
        return QHash<int, int>().value( l.slope.first ) ^ QHash<int, int>().value( l.slope.second )^
                QHash<int, int>().value(l.intercept.first) ^ QHash<int, int>().value(l.intercept.second );
    }
};


Line find_line_with_most_points( const vector< QPoint >& pts ){

    unordered_map< Line, unordered_set< QPoint, HashPoint>, HashLine > table;
    table.reserve( pts.size() * ( pts.size() - 1 ) );
    for( int i = 0, num = pts.size(); i < num; ++i ){
        for( int j = i+1; j < num; ++j ){
            Line l( pts[i], pts[j]);
            table[ l ].emplace( pts[i] );
            table[ l ].emplace( pts[j] );
        }
    }

    unordered_map< Line, unordered_set< QPoint, HashPoint>, HashLine >::const_iterator
            result = max_element( table.cbegin(), table.cend(),
                                  []( const pair<Line, unordered_set<QPoint, HashPoint>>& a,
                                      const pair<Line, unordered_set<QPoint, HashPoint>>& b ) {
                                          return a.second.size() < b.second.size();
                                      } );

    std::cout<<" find line with maximum of "<<result->second.size()<<" points "<<std::endl;
    return result->first;

}

#endif // HASHLINE_H
