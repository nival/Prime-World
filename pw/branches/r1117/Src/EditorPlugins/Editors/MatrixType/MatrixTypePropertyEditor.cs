using System;
using System.Collections.Generic;
using System.Text;
using EditorLib;
using System.ComponentModel;
using DBTypes;
using EditorLib.FieldProcessor;
using EditorLib.Extensions;
using System.Drawing.Design;

namespace EditorPlugins.Editors.MatrixType
{
	public sealed class MatrixTypePropertyEditorOld :TypePropertyEditor<Matrix>
	{
		protected override Matrix OpenDialog( Matrix _value, ITypeDescriptorContext context, IServiceProvider provider, IEditorWinApplication application )
		{
			Matrix value = new Matrix( null );
			Vec3 pos = new Vec3( null );
			float scale;
			float anglesX;
			float anglesY;
			float anglesZ;
			Quat rot = new Quat( null );
			MatrixTypePropertyEditorForm form = new MatrixTypePropertyEditorForm();
			MatrixUtils.Decompose( _value, out pos, out rot, out scale );

			MatrixUtils.ToEuler( rot, out anglesX, out anglesY, out anglesZ );

			form.textBox1.Text = System.Convert.ToString( pos.x );
			form.textBox2.Text = System.Convert.ToString( pos.y );
			form.textBox3.Text = System.Convert.ToString( pos.z );

			form.textBox6.Text = System.Convert.ToString( anglesX );
			form.textBox5.Text = System.Convert.ToString( anglesY );
			form.textBox4.Text = System.Convert.ToString( anglesZ );

			form.textBox7.Text = System.Convert.ToString( scale );

			form.ShowDialog();

			pos.x = (float)System.Convert.ToDouble( form.textBox1.Text );
			pos.y = (float)System.Convert.ToDouble( form.textBox2.Text );
			pos.z = (float)System.Convert.ToDouble( form.textBox3.Text );

			anglesX = (float)System.Convert.ToDouble( form.textBox6.Text );
			anglesY = (float)System.Convert.ToDouble( form.textBox5.Text );
			anglesZ = (float)System.Convert.ToDouble( form.textBox4.Text );

			scale = (float)System.Convert.ToDouble( form.textBox7.Text );

			MatrixUtils.FromEuler( out rot, anglesX, anglesY, anglesZ );

			MatrixUtils.Compose( out value, pos, rot, scale );

			return value;
		}
	}

	public sealed class MatrixTypePropertyEditor : TypedValueEditor<Matrix>
	{
		public MatrixTypePropertyEditor( IEditorWinApplication application ) : base( application ) { }
	
		protected override Matrix EditValue( ITypeDescriptorContext context, object instance, IServiceProvider provider, Matrix value )
		{
			Vec3 pos = new Vec3( null );
			float scale;
			float anglesX;
			float anglesY;
			float anglesZ;
			Quat rot = new Quat( null );
			MatrixTypePropertyEditorForm form = new MatrixTypePropertyEditorForm();
			MatrixUtils.Decompose( value, out pos, out rot, out scale );

			MatrixUtils.ToEuler( rot, out anglesX, out anglesY, out anglesZ );

			form.textBox1.Text = System.Convert.ToString( pos.x );
			form.textBox2.Text = System.Convert.ToString( pos.y );
			form.textBox3.Text = System.Convert.ToString( pos.z );

			form.textBox6.Text = System.Convert.ToString( anglesX );
			form.textBox5.Text = System.Convert.ToString( anglesY );
			form.textBox4.Text = System.Convert.ToString( anglesZ );

			form.textBox7.Text = System.Convert.ToString( scale );

			form.ShowDialog();

			pos.x = (float)System.Convert.ToDouble( form.textBox1.Text );
			pos.y = (float)System.Convert.ToDouble( form.textBox2.Text );
			pos.z = (float)System.Convert.ToDouble( form.textBox3.Text );

			anglesX = (float)System.Convert.ToDouble( form.textBox6.Text );
			anglesY = (float)System.Convert.ToDouble( form.textBox5.Text );
			anglesZ = (float)System.Convert.ToDouble( form.textBox4.Text );

			scale = (float)System.Convert.ToDouble( form.textBox7.Text );

			MatrixUtils.FromEuler( out rot, anglesX, anglesY, anglesZ );

			Matrix result = new Matrix( null );
			MatrixUtils.Compose( out result, pos, rot, scale );
			return result;
		}

		public override bool IsDropDownResizable { get { return false; } }
		public override UITypeEditorEditStyle EditorEditStyle { get { return UITypeEditorEditStyle.Modal; } }
	}
}