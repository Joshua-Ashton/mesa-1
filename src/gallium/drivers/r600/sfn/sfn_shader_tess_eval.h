#ifndef TEVALSHADERFROMNIR_H
#define TEVALSHADERFROMNIR_H

#include "sfn_shader_base.h"
#include "sfn_vertexstageexport.h"

namespace r600 {

class TEvalShaderFromNir : public VertexStage
{
public:
	TEvalShaderFromNir(r600_pipe_shader *sh, r600_pipe_shader_selector& sel,
                           const r600_shader_key& key, r600_shader *gs_shader);
        bool scan_sysvalue_access(nir_instr *instr) override;
        PValue primitive_id() override {return m_primitive_id;}
     private:
        bool allocate_reserved_registers() override;
        bool emit_intrinsic_instruction_override(nir_intrinsic_instr* instr) override;
        bool emit_load_tess_coord(nir_intrinsic_instr* instr);
        bool load_tess_z_coord(nir_intrinsic_instr* instr);

        bool do_process_inputs(nir_variable *input) override;
        bool do_process_outputs(nir_variable *output) override;
        bool do_emit_load_deref(const nir_variable *in_var, nir_intrinsic_instr* instr) override { return true;}
        bool do_emit_store_deref(const nir_variable *out_var, nir_intrinsic_instr* instr) override;
        void do_finalize() override;


        unsigned m_reserved_registers;
        PValue m_tess_coord[3];
        PValue m_rel_patch_id;
        PValue m_primitive_id;

        std::unique_ptr<VertexStageExportBase> m_export_processor;
        const r600_shader_key& m_key;
};


}

#endif // TEVALSHADERFROMNIR_H
