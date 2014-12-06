/*
 * file.h
 *
 *  Created on: 2014. 12. 6.
 *      Author: NCri
 */

#ifndef _FILE_H_
#define _FILE_H_

void save(P_HWATOO pilehead, P_HWATOO ahead, P_HWATOO bhead, P_HWATOO chead, P_HWATOO paehead,
		player_info *aplayer, player_info *bplayer, player_info *cplayer);
void load(P_HWATOO pilehead, P_HWATOO ahead, P_HWATOO bhead, P_HWATOO chead, P_HWATOO paehead,
		player_info *aplayer, player_info *bplayer, player_info *cplayer);

#endif /* _FILE_H_ */
