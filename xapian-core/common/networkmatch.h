/* networkmatch.h: class for communicating with remote match processes
 *
 * ----START-LICENCE----
 * Copyright 1999,2000 BrightStation PLC
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 * -----END-LICENCE-----
 */

#ifndef OM_HGUARD_NETWORKMATCH_H
#define OM_HGUARD_NETWORKMATCH_H

#include "match.h"
#include "stats.h"
#include "net_database.h"

/** Class for performing match calculations over a network interface.
 */
class NetworkMatch : public SingleMatch
{
    private:
	// disallow copies
	NetworkMatch(const NetworkMatch &);
	void operator=(const NetworkMatch &);

	// the database object
	NetworkDatabase *database;

	/// the statistics object
	Stats remote_stats;

	/// Prepare the stats object with contributed
	/// statistics from the remote end.
	void finish_query();

	/// The StatsSource object
	NetworkStatsSource statssource;

	/// A pointer to the gatherer, to access the statistics.
	StatsGatherer *gatherer;

	/// The maximum weight which can be returned
	om_weight max_weight;

	/// Indication of whether max_weight needs to be updated
	bool max_weight_needs_fetch;
    public:
        NetworkMatch(IRDatabase * database_);
        ~NetworkMatch();

	///////////////////////////////////////////////////////////////////
	// Implement these virtual methods
	void link_to_multi(StatsGatherer *gatherer);

	void set_query(const OmQueryInternal * query_);

	void set_rset(const OmRSet & omrset);
	void set_weighting(IRWeight::weight_type wt_type_);
	void set_options(const OmSettings & moptions_);

	bool prepare_match(bool nowait);

        om_weight get_max_weight();
	bool get_mset(om_doccount first,
		      om_doccount maxitems,
		      OmMSet &mset,
		      const OmMatchDecider *mdecider,
		      bool nowait
		     );

	///////////////////////////////////////////////////////////////////
	// Miscellaneous
	// =============

	/** Called by postlists to indicate that they've rearranged themselves
	 *  and the maxweight now possible is smaller.
	 */
        void recalc_maxweight();
};

#endif /* OM_HGUARD_NETWORKMATCH_H */
