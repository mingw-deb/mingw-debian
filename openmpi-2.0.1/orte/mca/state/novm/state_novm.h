/*
 * Copyright (c) 2011-2012 Los Alamos National Security, LLC.
 *                         All rights reserved.
 *
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

/**
 * @file
 *
 */

#ifndef MCA_STATE_NOVM_EXPORT_H
#define MCA_STATE_NOVM_EXPORT_H

#include "orte_config.h"

#include "orte/mca/state/state.h"

BEGIN_C_DECLS

/*
 * Local Component structures
 */

ORTE_MODULE_DECLSPEC extern orte_state_base_component_t mca_state_novm_component;

ORTE_DECLSPEC extern orte_state_base_module_t orte_state_novm_module;

END_C_DECLS

#endif /* MCA_STATE_NOVM_EXPORT_H */
