/* test utoa or utoa */

#include <stdio.h>

extern char *utoa( char *string, signed int num );

int main()
{
  signed int num;
  char buffer[ 12 ];

  puts( "Enter number:" );

  if( scanf( "%d", &num ) == 1 )
  {
    *utoa( buffer, num ) = 0; /* add string terminator */
    puts( "utoa yields:" );
    puts( buffer );
  }

  return( 0 );
}
